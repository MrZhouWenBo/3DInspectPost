#include "tools.h"
#include "postorocessAPI.h"

/**
 * 测试后处理接口的正确性  方法 直接使用模型导出的数据做测试
 * 存储 后处理结果用 python代码显示 进行查看
*/
void testPost()
{
    int b = 1;
    int c = 10;
    int h = 50;
    int w = 42;
    std::string path = "../testData/model_data/";
    std::string fileName = "_hm.txt";
    float heatmap_data[b * c * h * w];
    int len = b * c * h * w;
    readTxt(path + fileName, heatmap_data, len);
    
    fileName = "_center.txt";
    float center_data[b * 2 * h * w];
    len = 2 * b * h * w;
    readTxt(path + fileName, center_data, len);

    fileName = "_center_Z.txt";
    float center_Z_data[b * 1 * h * w];
    len = 1 * b * h * w;
    readTxt(path + fileName, center_Z_data, len);


    fileName = "_dim.txt";
    float dim_data[b * 3 * h * w];
    len = 3 * b * h * w;
    readTxt(path + fileName, dim_data, len);

    fileName = "_sin.txt";
    float sin_data[b * 1 * h * w];
    len = 1 * b * h * w;
    readTxt(path + fileName, sin_data, len);


    fileName = "_cos.txt";
    float cos_data[b * 1 * h * w];
    len = 1 * b * h * w;
    readTxt(path + fileName, cos_data, len);

    modelOutshape heatmap_shape;
    heatmap_shape.b =1;
    heatmap_shape.c = 10;
    heatmap_shape.h = h;
    heatmap_shape.w = w;
    std::vector<TargetBox_3D> _3DBoxs, final_3DBoxes;
    gen3D_Box(heatmap_data, center_data, center_Z_data, dim_data, sin_data, cos_data,\
    heatmap_shape, _3DBoxs, score_thresh);

    std::cout<<"__________" << std::endl;

    nms_3d_box(_3DBoxs, final_3DBoxes, nms_thresh);


    float boxes[final_3DBoxes.size()*7];
    float scores[final_3DBoxes.size()];
    float labels[final_3DBoxes.size()];

    int ids = 0;
    for (int i = 0; i < final_3DBoxes.size(); i++)
    {
        std::cout << final_3DBoxes[i].lable << std::endl;
        for (int j = 0; j < 6; j++)
        {
            boxes[ids * 7 + j] = final_3DBoxes[i].box[j];
        }
        boxes[ids*7 + 6] = final_3DBoxes[i].angle;

        scores[ids] = final_3DBoxes[i].score;
        labels[ids] = final_3DBoxes[i].lable;   
        ids++;
    }
    std::cout << "size is:" << final_3DBoxes.size() << std::endl;
    writeTxt(path + "boxes.txt", boxes, final_3DBoxes.size()*7);
    writeTxt(path + "scores.txt", scores, final_3DBoxes.size());
    writeTxt(path + "labels.txt", labels, final_3DBoxes.size());
}

/**
 * 接口测试成功后  测试ONNX推理结果
*/
void testONNX()
{
    int b = 1;
    int c = 10;
    int h = 50;
    int w = 42;
    std::string path = "../testData/inferenceData/";
    std::string fileName = "_hm.txt";
    float heatmap_data[b * c * h * w];
    int len = b * c * h * w;
    readTxt(path + fileName, heatmap_data, len);
    
    fileName = "_center.txt";
    float center_data[b * 2 * h * w];
    len = 2 * b * h * w;
    readTxt(path + fileName, center_data, len);

    fileName = "_center_Z.txt";
    float center_Z_data[b * 1 * h * w];
    len = 1 * b * h * w;
    readTxt(path + fileName, center_Z_data, len);


    fileName = "_dim.txt";
    float dim_data[b * 3 * h * w];
    len = 3 * b * h * w;
    readTxt(path + fileName, dim_data, len);

    fileName = "_sin.txt";
    float sin_data[b * 1 * h * w];
    len = 1 * b * h * w;
    readTxt(path + fileName, sin_data, len);


    fileName = "_cos.txt";
    float cos_data[b * 1 * h * w];
    len = 1 * b * h * w;
    readTxt(path + fileName, cos_data, len);

    modelOutshape heatmap_shape;
    heatmap_shape.b =1;
    heatmap_shape.c = 10;
    heatmap_shape.h = h;
    heatmap_shape.w = w;
    std::vector<TargetBox_3D> _3DBoxs, final_3DBoxes;
    gen3D_Box(heatmap_data, center_data, center_Z_data, dim_data, sin_data, cos_data,\
    heatmap_shape, _3DBoxs, score_thresh);

    std::cout<<"__________" << std::endl;

    nms_3d_box(_3DBoxs, final_3DBoxes, nms_thresh);


    float boxes[final_3DBoxes.size()*7];
    float scores[final_3DBoxes.size()];
    float labels[final_3DBoxes.size()];

    int ids = 0;
    for (int i = 0; i < final_3DBoxes.size(); i++)
    {
        std::cout << final_3DBoxes[i].lable << std::endl;
        for (int j = 0; j < 6; j++)
        {
            boxes[ids * 7 + j] = final_3DBoxes[i].box[j];
        }
        boxes[ids*7 + 6] = final_3DBoxes[i].angle;

        scores[ids] = final_3DBoxes[i].score;
        labels[ids] = final_3DBoxes[i].lable;   
        ids++;
    }
    std::cout << "size is:" << final_3DBoxes.size() << std::endl;
    writeTxt(path + "boxes.txt", boxes, final_3DBoxes.size()*7);
    writeTxt(path + "scores.txt", scores, final_3DBoxes.size());
    writeTxt(path + "labels.txt", labels, final_3DBoxes.size());
}


int main()
{
    testPost();
    testONNX();
    
    
    return 0;
}