import cv2
import sys

# Get user supplied values
imagePath = sys.argv[1]
cascPath  = sys.argv[2]

# Create the haar cascade
faceCascade = cv2.CascadeClassifier(cascPath)

"""
Now create the cascade and initialize it with our face
cascade. This loads the face cascade into memory so it's
ready for use. The cascade is an XML file that
contains the data to detect faces
"""
# Read the image
image = cv2.imread(imagePath)
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

"""
Read the image and convert it to grayscale.
Many operations in OpenCV are done in grayscale.
This is the CORE of the code:
- detectMultiSclae function is a general
  function that detects objects. Since we are calling
  on the face cascade, that's what it detects.
  -- gray means to the grayscale image
  -- scaleFactor: Since some faces may be closer to the
                  camera, they would appear bigger than 
                  those faces in the back. The scale scaleFactor
                  compensates for this.
  -- minNeighbors: defines how many objects are detected near the 
          		  current one befor it declares the face found.
          		  minSize gives the size of each window.

"""
# Detect faces in the image
faces = faceCascade.detectMultiScale(
    gray,
    scaleFactor  = 1.1,
    minNeighbors = 5,
    minSize      = (30, 30),
    flags        = cv2.cv.CV_HAAR_SCALE_IMAGE
)

"""
The function returns a list of rectangles where it believes
it found a face.
"""
print "Found {0} faces!".format(len(faces))
"""
loop over where it thinks it found something
"""
# Draw a rectangle around the faces
for (x, y, w, h) in faces:
    cv2.rectangle(image, (x, y), (x+w, y+h), (0, 255, 0), 2)

cv2.imshow("Faces found", image)
cv2.waitKey(0)