import numpy as np
from osgeo import gdal
import sys
from osgeo.gdalconst import GA_ReadOnly,GDT_Float32

def pca(infile,outfile):
    gdal.AllRegister()
    inDataset = gdal.Open(infile,GA_ReadOnly)
    cols = inDataset.RasterXSize
    rows = inDataset.RasterYSize
    bands = inDataset.RasterCount

  # матрица ‘data’
   G = np.zeros((rows*cols,bands))
   k=0
   for b in range(bands):
	band = inDataset.GetRasterBand(b+1)
  	mp = band.ReadAsArray(0,0,cols,rows)\
   			.astype(float).ravel()
	G[:,b] = tmp - np.mean(tmp)

   # матрица ковариации
   C = np.mat(G).T*np.mat(G)/(cols*rows-1)

   # Диагонализованная матрица
   lams,U = np.linalg.eigh(C)

   # Сортировка
   idx = np.argsort(lams)[::-1]
   lams = lams[idx]
   U = U[:,idx]

   # project
   PCs = np.reshape(np.array(G*U),(rows,cols,bands))

   # Сохраняем результат
  if outfile:
	driver = gdal.GetDriverByName(’Geotiff’)
	outDataset = driver.Create(outfile,
			cols,rows,bands,GDT_Float32)
	projection = inDataset.GetProjection()
	if projection is not None:
		outDataset.SetProjection(projection)
	for k in range(bands):
	    outBand = outDataset.GetRasterBand(k+1)         				    outBand.WriteArray(PCs[:,:,k],0,0)
            outBand.FlushCache()
	outDataset = None
  inDataset = None
# Здесь я ввожу именена сцен через консоль, но можно и сразу локально = “..”
infile = sys.argv[1]
outfile = sys.argv[2]
pca(infile,outfile)
Теперь для второй сцены все тоже самое
infile2 = sys.argv[1]
outfile2 = sys.argv[2]
dif_image = abs(double(outfile-outfile2))
# h – число блоков пикселей в изображение(может быть разным) и задается юзером
vector_s = zeros(rows*cols, 3*h*h)
mean_vector = mean(vector_s, 1)
dif_vector = vector_s – mean_vector
matrix_cov = cov(dif_vector)
eigvector = eig(matrix_covar)
eigvalue = eigvalue(eigvector)
for k in range(length(eigvalue)
	if(sum(eigvalue(k1:length(eigvalue)))>=
eigvector = eigvector(length(eigvalue))
feature = vector_set * eigvector
# K-means algorithm // немного псевдо кода
[label,~] = kmeans(feature,2)
CD = reshape(label, [row cols])
CD = CD – 1; // подгон размера
subplot(2,2,4);
imshow(CD,[])
title(‘CHANGE DETECTION’)
