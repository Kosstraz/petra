#include "engine/C/petra_images.h"
#include <stdio.h>

int main()
{
    uint8* datas;
    img_infos info = png_load("resources/images/blocks/dirt.png", &datas);

    printf("errorCode : %d\n", info.errorCode);

    return (0);
}