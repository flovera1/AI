"""
In here we'll be learning about the really basics about opencv
specifically how to read an image, how to display
and save it.
Functions introduced:
-cv2.imread()
-cv2.imshow()
-cv2.imwrite()
We'll also see how to display images with Matplotlib!
"""
#cv2.imread() is used to read an image.
#the image should be working in the directory
#or a full path should be given.
#the second argument is a flag which specifies the way
#the image should be read
"""
cv2.IMREAD_COLOR: loads a color image.
cv2.IMREAD_GRAYSCLAE: loads image in grayscle mode
cv2.IMREAD_UNCHANGED: loads image as such including
	 	 	 	 	  alpha channel

instead of the flags you can pass 1, 0, -1 respectively
"""
import numpy as np 
import cv2

#load a color image in grayscale
img = cv2.imread('mess15.jpg', 0)
#cv2.imshow() to display an image in a window
#first arg is name of the window
#second is the image itself
cv2.imshow('image', img)
cv2.waitKey(0)
cv2.destroyAllWindows()
cv2.namedWindow('image', cv2.WINDOW_NORMAL)
cv2.imshow('image',img)
cv2.waitKey(0)
cv2.destroyAllWindows()
cv2.imwrite('messigray.png',img)

