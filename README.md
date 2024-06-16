# ImageProcessing

Application used to test chain effect of image filters.
It takes as input loaded image or camera device.

![startup](https://github.com/kamilkozdro/ImageProcessing/assets/8678160/41f92e22-c97b-4074-85aa-4f955b8dccd5)

## How to use

1. Choose source of image:
   - Press "Load Image" button and select image to be processed.
   - Or click "Open Cam" to set camera as source of images. It will take frames from camera at 10 msec intervals. Number next to "Open Cam" button is a device number. If value is 0, application opens default camera device. If theres more than one device and you want to open a specific one, enter it's device ID (found in device manager).
2. From "Filters" box select a filter you want to use and click "Add" button. Select filter will appear in used filters list.
4. "Remove" button will remove selected filter from list.
5. Selecting used filter from list displays its parameters in "Filter Parameters" box. Fill parameters and click "Save" button to apply new values to filter.

![blur_image](https://github.com/kamilkozdro/ImageProcessing/assets/8678160/5a704fc3-d66c-4f20-94f0-d4f6ad6824b6)

6. Application has two windows that shows origin image or effects of filters. You can choose which image to display by selecting it from combo box located beneath image window.
7. Application apply one filter on another. So if you add Blur and then Sobel filter, image window with Sobel selected will display chain effect of filters used on source image ( source -> blurred source -> sobel on blurred source -> display )

![blur_sobel_image](https://github.com/kamilkozdro/ImageProcessing/assets/8678160/40b75be7-d779-4163-8c24-f5fd0107a923)
