# Object-Recognition-And-Counting

<img width="796" alt="1" src="https://github.com/canozgan/Object-Recognition-And-Counting/assets/129083272/69b2bea7-b834-41dc-9381-bf8d99c24ef0">

<img width="796" alt="2" src="https://github.com/canozgan/Object-Recognition-And-Counting/assets/129083272/646ed5f3-b226-4c6b-be4a-ca7153fdb5ee">


General Spesifications

1)This project is a Computer Vision Project that detects the location of objects in the picture, tells what these objects are and how many objects are in the picture.

2)If the user wants, he can teach new objects to the program.

3)The functions used in this project are unique. OpenCV is not used. Only the open source stb_image library is used to read RGB images from disk.


Technical Spesifications

1)This project is a Windows Form Application written in C and C++.

2)The necessary algorithms are divided into 4 phases. These phases are Clustering, Morphology, Labeling and Classification.

3)During the Clustering phase, the RGB format image is first converted to an Intensity image and then to a Binary image(1 is foreground, 0 is background).

4)If there is a glare that occurred while the photo was taken, it will be removed in the Morphology stage.

5)In the Labeling phase, objects are labeled and the border pixels of each object are determined.

6)During the Clussification phase, the properties of the labelled objects are extracted. If the user clicks on the Training section, the average of the properties of the objects in the picture is recorded. If the user clicks on the Testing section, it is said what each object in the picture is by looking at the previously recorded data.
