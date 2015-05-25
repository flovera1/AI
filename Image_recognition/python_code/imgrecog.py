from PIL import Image
import numpy as np 

i   = Image.open('images/dot.png')
iar = np.asarray(i) #split the image into an array
					#each subarray is a row within an image
					#each row is a pixel!!
					#the 4 coordenates means the color of the RGB
print iar