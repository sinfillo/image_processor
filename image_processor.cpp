#include "bmp.h"
#include "Image.h"
#include "Filter.h"
#include "Crop.h"
#include "Grayscale.h"
#include "Negative.h"
#include "MatrixFilter.h"
#include "Sharpening.h"
#include "EdgeDetection.h"
#include "GaussianBlur.h"
#include "Distortion.h"

int main(int argc, char** argv) {
    /*if (argc == 1) {
        static const auto REFERENCE =
            "Image Processor\n"
            "Applying filters to your photos.\n"
            "Only 24-bit .bmp files supported.\n"
            "How to use?\n"
            "The command must be entered in the following format: ./image_processor input.bmp output.bmp -[filter1] "
            "{arg1_1}... {arg1_n}...-[filter2] {arg2_1}...{arg2_k}...\n"
            "Argument list can be empty. The input file will be written to the output file.\n"
            "Filters are applied in the order they are listed.\n"
            "For example: ./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5\n"
            "Commands:\n"
            "  1. Crop filter          (-crop width height)\n"
            "  2. Grayscale filter     (-gs)\n"
            "  3. Negative filter      (-neg)\n"
            "  4. Sharpening filter    (-sharp)\n"
            "  5. Edge Detection       (-edge threshold)\n"
            "  6. Gaussian Blur        (-blur sigma)\n"
            "  7.Distortion filter     (-dist cnt_iters)";
        std::cout << REFERENCE << std::endl;
        return 0;
    }
    if (argc == 2) {
        throw std::runtime_error("No output file");
    }
    std::vector<std::string> command;
    size_t n = static_cast<size_t>(argc);
    for (size_t i = 0; i < n; ++i) {
        command.push_back(argv[i]);
    }
    Image image;
    const std::string input_file = command[1];
    const std::string output_file = command[2];
    const std::string file_format = ".bmp";
    if (file_format != input_file.substr(input_file.size() - 4, 4)) {
        throw std::runtime_error("This file format is not supported");
    }
    if (file_format != output_file.substr(output_file.size() - 4, 4)) {
        throw std::runtime_error("This file format is not supported");
    }
    Bmp file_operation_read(input_file, false);
    image = file_operation_read.Read();
    if (image.GetFileSize() == 0) {
        throw std::runtime_error("Empty file");
    }
    for (size_t i = 3; i < n; ++i) {
        const std::string cur_filter = command[i];
        if (cur_filter == "-gs") {
            Grayscale grayscale_filter;
            image = grayscale_filter.Apply(image);
        } else if (cur_filter == "-neg") {
            Negative negative_filter;
            image = negative_filter.Apply(image);
        } else if (cur_filter == "-sharp") {
            Sharpening sharpening_filter;
            image = sharpening_filter.Apply(image);
        } else if (cur_filter == "-edge") {
            if (n - i <= 1) {
                throw std::runtime_error("No threshold for filter Edge detection");
            }
            const std::string threshold_s = command[++i];
            double threshold = 0;
            try {
                threshold = std::stof(threshold_s);
            } catch (std::invalid_argument) {
                throw std::runtime_error("Threshold is not double");
            }
            EdgeDetection edge_filter(threshold);
            image = edge_filter.Apply(image);
        } else if (cur_filter == "-crop") {
            if (n - i <= 2) {
                throw std::runtime_error("No width/height for filter Crop");
            }
            const std::string width_s = command[++i];
            const std::string height_s = command[++i];
            int64_t width = 0;
            try {
                std::cerr << width_s << std::endl;
                width = std::stoi(width_s);
            } catch (std::invalid_argument) {
                throw std::runtime_error("Width is not integer");
            }
            int64_t height = 0;
            try {
                height = std::stoi(height_s);
            } catch (std::invalid_argument) {
                throw std::runtime_error("Height is not integer");
            }
            if (width < 0) {
                throw std::runtime_error("Width is not positive integer");
            }
            if (height < 0) {
                throw std::runtime_error("Height is not positive integer");
            }
            Crop crop_filter(height, width);
            image = crop_filter.Apply(image);
        } else if (cur_filter == "-blur") {
            if (n - i <= 1) {
                throw std::runtime_error("No sigma for filter Edge detection");
            }
            const std::string sigma_s = command[++i];
            double sigma = 0;
            try {
                sigma = std::stof(sigma_s);
            } catch (std::invalid_argument) {
                throw std::runtime_error("Sigma is not double");
            }
            GaussianBlur gaussian_filter(sigma);
            image = gaussian_filter.Apply(image);
        } else if (cur_filter == "-dist") {
            if (n - i <= 1) {
                throw std::runtime_error("No cnt_iters for Distortion filter");
            }
            const std::string cnt_iters_s = command[++i];
            int64_t cnt_iters = 0;
            try {
                cnt_iters = std::stoi(cnt_iters_s);
            } catch (std::invalid_argument) {
                throw std::runtime_error("cnt_iters is not integer");
            }
            if (cnt_iters < 0) {
                throw std::runtime_error("cnt_iters is not positive integer");
            }
            Distortion distortion_filter(cnt_iters);
            image = distortion_filter.Apply(image);
        } else {
            throw std::runtime_error("Incorrect filter");
        }
    }
    Bmp file_operation_write(output_file, true);
    file_operation_write.Print(image);*/
    Bmp
    file_operation_read("/Users/sinfillo/pmi-2210-1-Daria-Fomina-sinfillo/tasks/image_processor/test_images/hse_fu.bmp", false);
    Image image = file_operation_read.Read();
    Distortion distortion_filter(400);
    Image ans = distortion_filter.Apply(image);
    Bmp file_operation_write1("/Users/sinfillo/pmi-2210-1-Daria-Fomina-sinfillo/tasks/image_processor/test_images/hse_fu400.bmp", true);
    file_operation_write1.Print(ans);
    return 0;
}
