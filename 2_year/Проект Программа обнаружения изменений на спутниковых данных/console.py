import PySimpleGUI as sg
import os.path
import
from PIL import Image


# First window
def make_win1():
    layout = [[sg.Text('Date Before, dd.mm.yyyy'), sg.InputText()],
              [sg.Text('Date After, dd.mm.yyyy'), sg.InputText()],
              [sg.Button('OK'), sg.Button('Exit')]]
    return sg.Window('Change Detection', layout, location=(800, 600), finalize=True)


# Result window
def make_win2():
    file_list_column = [
        [
            sg.Text("Result"),
            sg.In(size=(25, 1), enable_events=True, key="-FOLDER-"),
            sg.FolderBrowse(),
        ],
        [
            sg.Listbox(
                values=[], enable_events=True, size=(40, 20), key="-FILE LIST-"
            )
        ],
    ]
    image_viewer_column = [
        [sg.Text("Result Image")],
        [sg.Text(size=(40, 1), key="-TOUT-")],
        [sg.Image(key="-IMAGE-")],
    ]
    layout = [
        [
            sg.Column(file_list_column),
            sg.VSeperator(),
            sg.Column(image_viewer_column),
        ]
    ]
    return sg.Window('Change Detection', layout, finalize=True)


# Main
window1, window2 = make_win1(), None  # start off with 1 window open
while True:  # Event Loop
    window, event, values = sg.read_all_windows()
    print('Date Before:', values[0], '\n', 'Date After:', values[1])
    if event == sg.WIN_CLOSED or event == 'Exit':
        window.close()
        if window == window2:  # if closing win 2, mark as closed
            window2 = None
        elif window == window1:  # if closing win 1, exit program
            break
    elif event == 'OK' and not window2:
        window2 = make_win2()
    elif event == "-FOLDER-":
        folder = values["-FOLDER-"]
        try:
            # Get list of files in folder
            file_list = os.listdir(folder)
        except:
            file_list = []

        fnames = [
            f
            for f in file_list
            if os.path.isfile(os.path.join(folder, f))
               and f.lower().endswith((".png", ".gif"))
        ]
        window2["-FILE LIST-"].update(fnames)
    elif event == "-FILE LIST-":  # A file was chosen from the listbox
        try:
            filename = os.path.join(
                values["-FOLDER-"], values["-FILE LIST-"][0]
            )
            window2["-TOUT-"].update(filename)
            window2["-IMAGE-"].update(filename=filename)
        except:
            pass
window.close()