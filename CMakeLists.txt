add_executable(
        image_processor
        image_processor.cpp
        Image.cpp Image.h
        bmp.cpp bmp.h
        Filter.h Filter.cpp
        Crop.h Crop.cpp
        Grayscale.h Grayscale.cpp
        Negative.h Negative.cpp
        MatrixFilter.cpp MatrixFilter.h
        Sharpening.h Sharpening.cpp
        EdgeDetection.h EdgeDetection.cpp
        reference
        GaussianBlur.h GaussianBlur.cpp
        Distortion.h Distortion.cpp)
add_catch(test_image
        test.cpp
        bmp.cpp
        Image.cpp
        Filter.cpp
        Crop.cpp
        Grayscale.cpp
        Negative.cpp
        MatrixFilter.cpp
        Sharpening.cpp
        EdgeDetection.cpp
        GaussianBlur.cpp
        Distortion.cpp
        )
