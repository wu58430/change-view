#define RESULT_ROW 100//结果图行列
#define RESULT_COL 114
#define         USED_ROW                120  //用于透视图的行列
#define         USED_COL                188
#define PER_IMG     SimBinImage//SimBinImage:用于透视变换的图像
#define ImageUsed   *PerImg_ip//*PerImg_ip定义使用的图像，ImageUsed为用于巡线和识别的图像
typedef unsigned char       uint8_t;                                              // 无符号  8 bits
uint8_t *PerImg_ip[RESULT_ROW][RESULT_COL];

void ImagePerspective_Init(void) {

    static uint8_t BlackColor = 0;
    double change_un_Mat[3][3] = {          //114w*100h
            { -0.01609759704190238, 0.01932561893613478, -2.040617594981866 }, {
                    0.0004352209945470896, -0.000367865364438621,
                    -0.7035606436969671 }, { 1.115951268069474e-005,
                    0.0001970185393508392, -0.03104642853440032 }, };
    for (int i = 0; i < RESULT_COL ;i++) {
        for (int j = 0; j < RESULT_ROW ;j++) {
            int local_x = (int) ((change_un_Mat[0][0] * i
                    + change_un_Mat[0][1] * j + change_un_Mat[0][2])
                    / (change_un_Mat[2][0] * i + change_un_Mat[2][1] * j
                            + change_un_Mat[2][2]));
            int local_y = (int) ((change_un_Mat[1][0] * i
                    + change_un_Mat[1][1] * j + change_un_Mat[1][2])
                    / (change_un_Mat[2][0] * i + change_un_Mat[2][1] * j
                            + change_un_Mat[2][2]));
            if (local_x
                    >= 0&& local_y >= 0 && local_y < USED_ROW && local_x < USED_COL){
                PerImg_ip[j][i] = &PER_IMG[local_y][local_x];
            }
            else {
                PerImg_ip[j][i] = &BlackColor;          //&PER_IMG[0][0];
            }

        }
    }

}


/*完成摄像头初始化后，调用一次ImagePerspective_Init，此后，直接调用ImageUsed   即为透视结果*/