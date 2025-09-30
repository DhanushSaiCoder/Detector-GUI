#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // 1. Create a VideoCapture object to connect to the default camera (ID 0)
    cv::VideoCapture cap(0);

    // 2. Check if the camera was opened successfully
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return -1; // Exit the program with an error code
    }

    // 3. Create a Matrix (Mat) object to store each frame from the camera
    cv::Mat frame;

    // 4. Create a window to display the video
    cv::namedWindow("Webcam Feed", cv::WINDOW_AUTOSIZE);

    // 5. Loop forever until the user presses the ESC key
    while (true) {
        // Read a new frame from the camera
        cap >> frame;

        // If the frame is empty (e.g., camera disconnected), break the loop
        if (frame.empty()) {
            std::cerr << "Error: Captured an empty frame." << std::endl;
            break;
        }

        // Display the captured frame in the "Webcam Feed" window
        cv::imshow("Webcam Feed", frame);

        // Wait for 1 millisecond for a key press.
        // If the pressed key is ESC (ASCII value 27), break the loop.
        if (cv::waitKey(1) == 27) {
            std::cout << "ESC key pressed. Exiting..." << std::endl;
            break;
        }
    }

    return 0;
}
