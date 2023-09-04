#include "catch.hpp"
#include "Image.h"
#include "bmp.h"

TEST_CASE("bebra") {
    Bmp reader;
    Image ans =
        reader.Read("/Users/sinfillo/pmi-2210-1-Daria-Fomina-sinfillo/tasks/image_processor/test_images/test4pix.bmp");
    REQUIRE(ans.GetHeight() == 2);
    REQUIRE(ans.GetWidth() == 2);
}
