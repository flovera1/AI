import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn import svm

digits = datasets.load_digits() #Load and return the digits dataset (classification).
"""
print(digits.data)
print(digits.target)
print(digits.images[0])
"""
clf  = svm.SVC(gamma = 0.001, C = 100) 
#print(len(digits.data))
#training the data
x, y = digits.data[:-10], digits.target[:-10] #storing all the answers
clf.fit(x, y)
print('Prediction:', clf.predict(digits.data[-6]))
#show the image of the digit that we are printing
plt.imshow(digits.images[-1], cmap = plt.cm.gray_r, interpolation = "nearest")
plt.show()