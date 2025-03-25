#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include <algorithm>

/*
This project combines basic physics, signal processing, and image processing concepts
by simulates a simple electrical circuit using Ohm's Law to generate a voltage signal. 
This signal is then analyzed using a Discrete Fourier Transform (DFT) to understand
its frequency components. Then, the signal is visualized as an image by mapping
the signal values to pixel intensities, simulating an image processing task.
*/
//Year: 2023
//Currently editing: 2025
// Updated comments: 2025

// Constants for Circuit Simulation (Physics Circuits)
const double RESISTANCE = 100.0;  // Resistor in ohms
const double VOLTAGE = 5.0;       // Voltage in Volts
const double FREQUENCY = 50.0;    // Frequency of AC source in Hz

// Ohm's Law to calculate current
double calculateCurrent(double voltage, double resistance) {
    return voltage / resistance;  // I = V / R
}

// Signal Generation: A simple AC signal simulation using the formula for sinusoidal voltage
std::vector<double> generateACSignal(double frequency, double timeInterval, int numSamples) {
    std::vector<double> signal(numSamples);
    double sampleRate = numSamples / timeInterval;
    
    for (int i = 0; i < numSamples; ++i) {
        double time = i / sampleRate;
        // Generate an AC signal using the formula: V(t) = Vmax * sin(2 * pi * f * t)
        signal[i] = VOLTAGE * sin(2 * M_PI * frequency * time);
    }

    return signal;
}

// Signal Processing: DFT (Discrete Fourier Transform) for frequency analysis
void performDFT(const std::vector<double>& signal) {
    int N = signal.size();
    std::vector<std::complex<double>> dft(N);

    // Calculate the DFT using the standard formula
    for (int k = 0; k < N; ++k) {
        std::complex<double> sum(0, 0);
        for (int n = 0; n < N; ++n) {
            double angle = (2 * M_PI * k * n) / N;
            sum += std::polar(signal[n], -angle);  // Euler's formula e^(i*theta)
        }
        dft[k] = sum;
    }

    // Output the DFT result (Magnitude of the Fourier coefficients)
    std::cout << "\nDFT Output (Magnitude of Frequency Components):\n";
    for (int i = 0; i < N; ++i) {
        std::cout << "Frequency bin " << i << ": " << std::abs(dft[i]) << std::endl;
    }
}

// Image processing: Enhance an image by converting it to grayscale (simulating pixel data manipulation)
void enhanceImage(std::vector<std::vector<int>>& image) {
    // Iterate through all the pixels and convert to grayscale (average of RGB channels)
    for (size_t y = 0; y < image.size(); ++y) {
        for (size_t x = 0; x < image[y].size(); ++x) {
            int pixel = image[y][x];
            int r = (pixel >> 16) & 0xFF;  // Extract red
            int g = (pixel >> 8) & 0xFF;   // Extract green
            int b = pixel & 0xFF;          // Extract blue
            int gray = static_cast<int>(0.3 * r + 0.59 * g + 0.11 * b);  // Convert to grayscale
            image[y][x] = (gray << 16) | (gray << 8) | gray;  // Set grayscale value to RGB
        }
    }
}

// Function to simulate the visualization of the signal as an image
void visualizeSignalAsImage(const std::vector<double>& signal, int width, int height) {
    // Create a simple image represented as a 2D array of pixel values (use simple grayscale)
    std::vector<std::vector<int>> image(height, std::vector<int>(width, 0xFFFFFF));  // White background

    // Map the signal to image pixel values (simplified)
    for (int i = 0; i < signal.size(); ++i) {
        int pixelValue = static_cast<int>((signal[i] / VOLTAGE) * 255);  // Scale signal to 0-255
        pixelValue = std::max(0, std::min(255, pixelValue));  // Ensure valid pixel range [0, 255]

        // Map to image (wrap around width)
        int x = i % width;
        int y = i / width;

        if (y < height) {
            image[y][x] = (pixelValue << 16) | (pixelValue << 8) | pixelValue;  // Set pixel color to grayscale
        }
    }

    // Enhance image by converting to grayscale (already grayscale, but applying for consistency)
    enhanceImage(image);

    // Display the enhanced image (simulated by printing pixel values)
    std::cout << "\nEnhanced Image (Simulated Grayscale Visualization of Signal):\n";
    for (size_t y = 0; y < image.size(); ++y) {
        for (size_t x = 0; x < image[y].size(); ++x) {
            int pixel = image[y][x];
            std::cout << std::hex << pixel << " ";  // Print pixel as hex
        }
        std::cout << "\n";
    }
}

int main() {
    // Step 1: Circuit Calculation - Ohm's Law
    double current = calculateCurrent(VOLTAGE, RESISTANCE);
    std::cout << "Current in the circuit: " << current << " A\n";

    // Step 2: Signal Generation - Generate an AC signal using a simple sinusoidal function
    double timeInterval = 1.0;  // 1 second
    int numSamples = 100;       // 100 samples
    std::vector<double> signal = generateACSignal(FREQUENCY, timeInterval, numSamples);

    // Step 3: Signal Processing - Perform DFT (Frequency Analysis)
    performDFT(signal);

    // Step 4: Image Processing - Visualize the signal as an image
    int imageWidth = 10;  // Image width in pixels
    int imageHeight = 10; // Image height in pixels
    visualizeSignalAsImage(signal, imageWidth, imageHeight);

    return 0;
}
