from gdalconst import *
# необходимо для создания графиков
import matplotlib.pyplot as plt
# необходимо для работы с массивами
import numpy as np
# необходимо для вычисления mode массивов
from scipy import stats
# файлы со сценами
filename_t1 = "Sentinel2_RGB20210331.tif"
filename_t2 = "Sentinel2_RGB20180418.tif"
# параметры изображения
rows = 500
columns = 700
figure_border = 25
# Загружаю datasets
dataset_t1 = gdal.Open(filename_t1, GA_ReadOnly)
dataset_t2 = gdal.Open(filename_t2, GA_ReadOnly)
# Получаем информацию параметра B1 для обоих снимков
### NDVI
ndvi_t1 = dataset_t1.GetRasterBand(1)
ndvi_t2 = dataset_t2.GetRasterBand(1)
# Построим гистограммы для обоих снимков bands 1
plt.figure(figsize=(10, 8))
plt.plot(ndvi_t1.GetHistogram(), label="$I_{t_1}$")
plt.plot(ndvi_t2.GetHistogram(), label="$I_{t_2}$")
plt.legend()
plt.grid(b=True, color='gray', linestyle='--', linewidth=0.5);
# plt.savefig("histograms_t1xt2.png", format='png', dpi=200)
plt.show()
plt.close()
# Считаем индекс NDTS
array_t1 = ndvi_t1.ReadAsArray()[0:rows, 0:columns].astype(float)
array_t2 = ndvi_t2.ReadAsArray()[0:rows, 0:columns].astype(float)
array_ndts = (array_t2 - array_t1) / (array_t2 + array_t1)
# Строим первичный NDTS
output_fig, (ndts_ax, histogram_ax) = plt.subplots(figsize=(10, 3), ncols=2)
ndts_ax.imshow(array_ndts, cmap="gray")
ndts_ax.set_xlim([0 - figure_border, columns + figure_border])
ndts_ax.set_ylim([rows + figure_border, 0 - figure_border])
histogram_ax.hist(array_ndts.ravel(), bins=200, range=(-1.0, 1.0))
histogram_ax.grid(b=True, color='gray', linestyle='--', linewidth=0.5);
# output_fig.savefig("ndts.png", format='png', dpi=200)
plt.show()
plt.close()
# Применяю алгоритм улучшения
# квадрат NDTS
array_square_ndts = array_ndts * array_ndts
# Строим квадрат NDTS
output_fig, (square_ndts_ax, histogram_ax) = plt.subplots(figsize=(10, 3), ncols=2)
square_ndts_ax.imshow(array_square_ndts, cmap="gray")
square_ndts_ax.set_xlim([0 - figure_border, columns + figure_border])
square_ndts_ax.set_ylim([rows + figure_border, 0 - figure_border])
histogram_ax.hist(array_square_ndts.ravel(), bins=200, range=(-0.25, 0.25))
histogram_ax.grid(b=True, color='gray', linestyle='--', linewidth=0.5);
# output_fig.savefig("square_ndts.png", format='png', dpi=200)
plt.show()
plt.close()
# Метод threshold для выделения результатов в обнаружении изменений
threshold = 0.1
threshold_array_square_ndts = array_square_ndts > threshold
# Построим диаграмму с первичным обнаружением изменений
output_fig, threshold_ax = plt.subplots(figsize=(10, 8), ncols=1)
threshold_ax.imshow(threshold_array_square_ndts, cmap="gray")
threshold_ax.set_xlim([0 - figure_border, columns + figure_border])
threshold_ax.set_ylim([rows + figure_border, 0 - figure_border])
# output_fig.savefig("threshold_square_ndts.png", format='png', dpi=200)
plt.show()
plt.close()
# Применим алгорит 3x3 mode для уменьшение шумов
mode_threshold_array_square_ndts = threshold_array_square_ndts
for i in range(1,rows):
	for j in range(1,columns):
		values = np.array(threshold_array_square_ndts[i-1:i+2, j-1:j+2])
		mode_threshold_array_square_ndts[i, j] = stats.mode(values.ravel())[0][0]
# РЕЗУЛЬТАТ
# создадим фигуру уже отфильтрованного обнаружения изменений
output_fig, threshold_ax = plt.subplots(figsize=(10, 8), ncols=1)
threshold_ax.imshow(mode_threshold_array_square_ndts, cmap="gray")
threshold_ax.set_xlim([0 - figure_border, columns + figure_border])
threshold_ax.set_ylim([rows + figure_border, 0 - figure_border])
# output_fig.savefig("mode_threshold_square_ndts.png", format='png', dpi=200)
plt.show()
plt.close()
