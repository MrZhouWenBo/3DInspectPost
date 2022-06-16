#include "postorocessAPI.h"
#include <math.h>
#include <algorithm>
// 此处应暴露尽量多的接口便于测试模块正确性
inline void rotate_around_center(const Point &center, const float angle_cos, const float angle_sin, Point &p)
{
    float new_x = (p.x - center.x) * angle_cos + (p.y - center.y) * (-angle_sin) + center.x;
    float new_y = (p.x - center.x) * angle_sin + (p.y - center.y) * angle_cos + center.y;
    p.set(new_x, new_y);
}
inline float cross(const Point &p1, const Point &p2, const Point &p0)
{
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

inline float cross(const Point &a, const Point &b){
    return a.x * b.y - a.y * b.x;
}

inline int check_rect_cross(const Point &p1, const Point &p2, const Point &q1, const Point &q2){
    int ret = std::min(p1.x,p2.x) <= std::max(q1.x,q2.x)  &&
              std::min(q1.x,q2.x) <= std::max(p1.x,p2.x) &&
              std::min(p1.y,p2.y) <= std::max(q1.y,q2.y) &&
              std::min(q1.y,q2.y) <= std::max(p1.y,p2.y);
    return ret;
}

inline int intersection(const Point &p1, const Point &p0, const Point &q1, const Point &q0, Point &ans){
    // fast exclusion
    if (check_rect_cross(p0, p1, q0, q1) == 0) return 0;

    // check cross standing
    float s1 = cross(q0, p1, p0);
    float s2 = cross(p1, q1, p0);
    float s3 = cross(p0, q1, q0);
    float s4 = cross(q1, p1, q0);

    if (!(s1 * s2 > 0 && s3 * s4 > 0)) return 0;

    // calculate intersection of two lines
    float s5 = cross(q1, p1, p0);
    if(fabs(s5 - s1) > EPS){
        ans.x = (s5 * q0.x - s1 * q1.x) / (s5 - s1);
        ans.y = (s5 * q0.y - s1 * q1.y) / (s5 - s1);

    }
    else{
        float a0 = p0.y - p1.y, b0 = p1.x - p0.x, c0 = p0.x * p1.y - p1.x * p0.y;
        float a1 = q0.y - q1.y, b1 = q1.x - q0.x, c1 = q0.x * q1.y - q1.x * q0.y;
        float D = a0 * b1 - a1 * b0;

        ans.x = (b0 * c1 - b1 * c0) / D;
        ans.y = (a1 * c0 - a0 * c1) / D;
    }

    return 1;
}

inline int check_in_box2d(const float *box, const Point &p){
    //params: (7) [x, y, z, dx, dy, dz, heading]
    const float MARGIN = 1e-2;

    float center_x = box[0], center_y = box[1];
    float angle_cos = cos(-box[6]), angle_sin = sin(-box[6]);  // rotate the point in the opposite direction of box
    float rot_x = (p.x - center_x) * angle_cos + (p.y - center_y) * (-angle_sin);
    float rot_y = (p.x - center_x) * angle_sin + (p.y - center_y) * angle_cos;

    return (fabs(rot_x) < box[3] / 2 + MARGIN && fabs(rot_y) < box[4] / 2 + MARGIN);
}

inline int point_cmp(const Point &a, const Point &b, const Point &center){
    return atan2(a.y - center.y, a.x - center.x) > atan2(b.y - center.y, b.x - center.x);
}

inline float box_overlap(TargetBox_3D box1, TargetBox_3D box2)
{
    float box_a[7], box_b[7];
    for (int i = 0; i < 6; i++)
    {
        box_a[i] = box1.box[i];
        box_b[i] = box2.box[i];
    }
    box_a[6] = box1.angle;
    box_b[6] = box2.angle;

    float a_angle = box_a[6], b_angle = box_b[6];
    float a_dx_half = box_a[3] / 2, b_dx_half = box_b[3] / 2;
    float a_dy_half = box_a[4] / 2, b_dy_half = box_b[4] / 2;
    float a_x1 = box_a[0] - a_dx_half, a_y1 = box_a[1] - a_dy_half;
    float a_x2 = box_a[0] + a_dx_half, a_y2 = box_a[1] + a_dy_half;
    float b_x1 = box_b[0] - b_dx_half, b_y1 = box_b[1] - b_dy_half;
    float b_x2 = box_b[0] + b_dx_half, b_y2 = box_b[1] + b_dy_half;
    
    Point center_a(box_a[0], box_a[1]);
    Point center_b(box_b[0], box_b[1]);


    Point box_a_corners[5];
    box_a_corners[0].set(a_x1, a_y1);
    box_a_corners[1].set(a_x2, a_y1);
    box_a_corners[2].set(a_x2, a_y2);
    box_a_corners[3].set(a_x1, a_y2);

    Point box_b_corners[5];
    box_b_corners[0].set(b_x1, b_y1);
    box_b_corners[1].set(b_x2, b_y1);
    box_b_corners[2].set(b_x2, b_y2);
    box_b_corners[3].set(b_x1, b_y2);

    // get oriented corners
    float a_angle_cos = cos(a_angle), a_angle_sin = sin(a_angle);
    float b_angle_cos = cos(b_angle), b_angle_sin = sin(b_angle);

    for (int k = 0; k < 4; k++)
    {
        rotate_around_center(center_a, a_angle_cos, a_angle_sin, box_a_corners[k]);
        rotate_around_center(center_b, b_angle_cos, b_angle_sin, box_b_corners[k]);
    }
    // 蛇咬尾了
    box_a_corners[4] = box_a_corners[0];
    box_b_corners[4] = box_b_corners[0];

    // get intersection of lines
    Point cross_points[16];
    Point poly_center;
    int cnt = 0, flag = 0;

    poly_center.set(0, 0);
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            flag = intersection(box_a_corners[i + 1], box_a_corners[i], box_b_corners[j + 1], box_b_corners[j], cross_points[cnt]);
            if (flag)
            {
                poly_center = poly_center + cross_points[cnt];
                cnt++;
            }
        }
    }

    // check corners
    for (int k = 0; k < 4; k++){
        if (check_in_box2d(box_a, box_b_corners[k]))
        {
            poly_center = poly_center + box_b_corners[k];
            cross_points[cnt] = box_b_corners[k];
            cnt++;
        }
        if (check_in_box2d(box_b, box_a_corners[k]))
        {
            poly_center = poly_center + box_a_corners[k];
            cross_points[cnt] = box_a_corners[k];
            cnt++;
        }
    }

    poly_center.x /= cnt;
    poly_center.y /= cnt;

    // sort the points of polygon
    Point temp;
    for (int j = 0; j < cnt - 1; j++){
        for (int i = 0; i < cnt - j - 1; i++){
            if (point_cmp(cross_points[i], cross_points[i + 1], poly_center)){
                temp = cross_points[i];
                cross_points[i] = cross_points[i + 1];
                cross_points[i + 1] = temp;
            }
        }
    }

    // get the overlap areas
    float area = 0;
    for (int k = 0; k < cnt - 1; k++){
        area += cross(cross_points[k] - cross_points[0], cross_points[k + 1] - cross_points[0]);
    }

    return fabs(area) / 2.0;
}

float cal_3D_box_iou(TargetBox_3D box1, TargetBox_3D box2)
{
    float bev_square_box1 = box1.box[3] * box1.box[4];
    float bev_square_box2 = box2.box[3] * box2.box[4];
    float s_overlap = box_overlap(box1, box2);
    return s_overlap / fmaxf(bev_square_box1 + bev_square_box2 - s_overlap, EPS);
}


void top_K(float *data, int *index,int len,  int K)
{
    float curmax = 0;
    
    bool boolArray[len] = {0};
    
    // 装载每次找出的最大值的index
    int idx = 0;
   
    for (int i = 0; i < K; ++i)
    {
        float tempMax = 0;
        for (int j = 0; j < len; j++)
        {
            float currentvalue = data[j];
            if (boolArray[j] != 1 && currentvalue >= tempMax)
            {
                idx = j;
                tempMax = currentvalue;
            }
        }
        boolArray[idx] = 1;
        index[i] = idx;
    }
}


void gen3D_Box(float* hm, float* center, float * center_z, float * dim, float * angl_sin, float* angl_cos,\
 modelOutshape _shape, std::vector<TargetBox_3D> &resultBox, const float score_thresh)
 {
     TargetBox_3D temp_3D_Box;
     //遍历hm选出  得分大于score_thresh的点 并生成TargetBox_3D push到输出
     for (int i = 0; i < (_shape.b * _shape.c * _shape.h * _shape.w); i++)
     {
         if (hm[i] > score_thresh)
         {
            //0  获取当前得分
            float score = hm[i];
            //1  计算对应hm的index
            int index = i % (_shape.h * _shape.w);

            //2  计算box的中心 X Y
            //2.1   计算对应hm 的 ys 和 xs
            int ys = int(index / _shape.w);
            int xs = int(index % _shape.w);
            //2.2   从center[1 2 h w]中获取  注：center是个特征图维度上的偏移量 0->x  1->y
            float bias_X = center[_shape.h * _shape.w * 0 + index];
            float bias_Y = center[_shape.h * _shape.w * 1 + index];
            //2.3   计算最终box的中心点
            float X = (xs + bias_X) * featureStride * voxelSize + point_Cloud_range[0];
            float Y = (ys + bias_Y) * featureStride * voxelSize + point_Cloud_range[1];
            //3  获取中心点的Z
            float Z = center_z[index];

            //4  获取box的 dx dy dz         dim [1 3 h w]
            float dx = dim[_shape.h * _shape.w * 0 + index];
            float dy = dim[_shape.h * _shape.w * 1 + index];
            float dz = dim[_shape.h * _shape.w * 2 + index];

            //5  获取class_label
            int class_label = int(i / (_shape.h * _shape.w));

            //6  获取角度值
            float rot_sin = angl_sin[index];
            float rot_cos = angl_cos[index];
            
            temp_3D_Box.box[0] = X;
            temp_3D_Box.box[1] = Y;
            temp_3D_Box.box[2] = Z;
            temp_3D_Box.box[3] = dx;
            temp_3D_Box.box[4] = dy;
            temp_3D_Box.box[5] = dz;
            temp_3D_Box.score = score;
            temp_3D_Box.lable = class_label;
            temp_3D_Box.index = index;
            temp_3D_Box.angle = atan2(rot_sin, rot_cos);
            resultBox.push_back(temp_3D_Box);
         }
     }
     
 }

bool sort_score(TargetBox_3D box1, TargetBox_3D box2)
{
    return (box1.score > box2.score);
}



void nms_3d_box(std::vector<TargetBox_3D> &srcBoxes, std::vector<TargetBox_3D> &dstBoxes,\
const float iou_threshold)
{
    std::sort(srcBoxes.begin(), srcBoxes.end(), sort_score);

    std::vector<int> picked;
    for (int i = 0; i < srcBoxes.size(); i++) {
        int keep = 1;
        for (int j = 0; j < picked.size(); j++) {
            //交集
            float iou = cal_3D_box_iou(srcBoxes[i], srcBoxes[picked[j]]);
            if(iou > iou_threshold) {
                keep = 0;
                break;
            }
        }
        if (keep) {
            picked.push_back(i);
        }
    }
    
    for (int i = 0; i < picked.size(); i++) {
        dstBoxes.push_back(srcBoxes[picked[i]]);
    }

}




