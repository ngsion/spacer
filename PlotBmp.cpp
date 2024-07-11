#include "Utility.h"
#include "writeBMP.h"

#define PW 648
#define PH 480

#define SW (PW + 1)
#define SH (PH + 1)

bool LoadMatrixFileToA(const char *fileName, int row, int column, int A[SW][SH])
{

    ifstream fileStream;

    fileStream.open(fileName, std::ios::in);

    if (fileStream.fail())
    {
        cout << "read file failed " << fileName << endl;
        return false;
    }
    else
    {

        for (int y = column - 1; y >= 0; y--)
        {
            for (int x = 0; x < row; x++)
            {
                fileStream >> A[x][y];
            }
        }
    }

    return true;
}

int main()
{
    printf("start  \n");
    //  cout << "start with " << endl;

    int A[SW][SH];
    char filename[64] = "result_648X480_start_1_21_1160.txt";

    if (isFileExists_fopen(filename))
    {
        LoadMatrixFileToA(filename, SW, SH, A);
    }
    else
    {
        cout << "no file " << endl;

        return 0;
    }

    int width = PW;
    int height = PH;

    // Calculate size of image data
    int data_size = width * height * 3 * 4;
    unsigned char *RGBData = (unsigned char *)malloc(sizeof(unsigned char) * data_size);
    memset(RGBData, 255, sizeof(unsigned char) * data_size);

    int lengthInLine = width * 3 * 2;
    for (int ypos = SH - 1; ypos >= 0; ypos--)
    {

        int yy = 2 * (SH - ypos - 1);
        for (int xpos = 0; xpos < SW; xpos++)
        {

            int xx = 2 * xpos;

            int datapos1 = (yy - 1) * lengthInLine + (xx + 1) * 3;
            int datapos2 = yy * lengthInLine + xx * 3;
            int datapos3 = (yy + 1) * lengthInLine + (xx - 1) * 3;
            int datapos4 = (yy + 2) * lengthInLine + (xx - 2) * 3;

            //  cout << "a x y " << xpos << "  " << ypos << "  " << A[xpos][ypos] << endl;
            if (A[xpos][ypos] == 2)   ////upright
            {
                if (datapos1 > 0 && datapos1 < data_size - 2)
                {
                    *((unsigned char *)(RGBData + datapos1)) = 0;
                    *((unsigned char *)(RGBData + datapos1 + 1)) = 0;
                    *((unsigned char *)(RGBData + datapos1 + 2)) = 255;
                }
            }
            else  if (A[xpos][ypos] == 4)   ////downleft
            {
                if (datapos4 > 0 && datapos4 < data_size - 2)
                {
                    *((unsigned char *)(RGBData + datapos4)) = 0;
                    *((unsigned char *)(RGBData + datapos4 + 1)) = 255;
                    *((unsigned char *)(RGBData + datapos4 + 2)) = 0;
                }
            }

        }
    }

    writeBMP("image.bmp", height * 2, width * 2, RGBData);
    // Draw point
    free(RGBData);

    cout << "finish" << endl;
    return 0;
}
