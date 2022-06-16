#pragma once
#include <vector>
#include <type.h>

/**
 * 接口后续需要修改出入类型
 * @brief 获取输入数据的前K个值的index
 * @param data      待搜寻数据
 * @param len       数据长度
 * @param K         前K个值
 * @return index    返回序号  长度与K一致
*/
void top_K(float *data, int *index, int len,  int K = 100);
// void test();


/**
 * @brief   输入模型的输出结果，输出 TargetBox_3D 类型的结果
 * @param   hm center, center_z, dim, 'rot_cos', 'rot_sin'   这些后续都直接输入框架的推理结果数据
 * @param   _shape hm的尺寸
 * @param   featureStride * voxelSize + point_Cloud_range[0] 也需要加入！！！！！！！！！！！！
 * @param   score_thresh 选框的得分阈值
 * @return   vector<TargetBox_3D> &resultBox 输出结果
*/
void gen3D_Box(float* hm, float* center, float * center_z, float * dim, float * angl_sin, float* angl_cos,\
 modelOutshape _shape,std::vector<TargetBox_3D> &resultBox, const float score_thresh);


bool sort_score(TargetBox_3D box1, TargetBox_3D box2);

/**
 * @brief   3D框非极大值抑制   
 * @param   srcBoxex    输入3D框
 * @param   iou_threshold  nms时的threshold
 * @return  dstBoxes    输出3D框        
 */
void nms_3d_box(std::vector<TargetBox_3D> &srcBoxes, std::vector<TargetBox_3D> &dstBoxes,\
const float iou_threshold);

/**
 * @brief   计算两个3D_Box的IOU, 这里计算的是BEV的IOU
 * @param   box1  box1
 * @return  重叠百分比
*/
float cal_3D_box_iou(TargetBox_3D box1, TargetBox_3D box2);



