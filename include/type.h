class Point {
public:
    Point() {}
    Point(float _x, float _y) {
        x = _x;
        y = _y;
    }
    float x;
    float y;
    void set(float _x, float _y) {
        x = _x;
        y = _y;
    }
    Point operator +(const Point &b)const{
        return Point(x + b.x, y + b.y);
    }
    
    Point operator -(const Point &b)const{
        return Point(x - b.x, y - b.y);
    }
};

typedef struct _3DTargetBox
{
    float box[6];       // x y z dx dy dz
    float angle;        // arctan(sin/cos)
    float score;        //
    int lable;          //class ID 
    int index;          //存放位置用于验证       
}TargetBox_3D;

typedef struct _modelOutshape
{
    int b;
    int c;
    int h;
    int w;
}modelOutshape;

const float EPS = 1e-8;

float voxelSize = 0.2;
int featureStride = 4;
float score_thresh = 0.45;
float nms_thresh = 0.1;
float point_Cloud_range[6] = {0, -20, -1, 34, 20, 3};
