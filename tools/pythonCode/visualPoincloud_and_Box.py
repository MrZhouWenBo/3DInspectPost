from matplotlib.pyplot import box
import open3d, os, sys
import numpy as np
abPath = os.path.abspath(os.path.dirname(os.getcwd()))
print(abPath)
sys.path.append(abPath)
import open3d_vis_utils as V



def visual_PC_and_3DBoxes(poindClouds, _3DBoxes, scores, labels):
    '''
    @brief  此代码为显示3D检测模型所的Box用 单帧显示
    @param  _3DBoxes  n ,7维
    @param  scores    n, 1
    @param  label     n, 1
    '''
    V.draw_scenes(
                    points=poindClouds, ref_boxes=_3DBoxes,
                    ref_scores=scores, ref_labels=labels)


PCpath = "/media/jose/6842930A30C05552/3Drecgonization/code"\
    "/Transplantation_model/OpenPCDet_Train/Ztest/finalInferenceReault"
PC = np.load(os.path.join(PCpath, 'points.npy'))[:, 1:]



onnxpath = "/media/jose/6842930A30C05552/3Drecgonization/code/codeBackUp/toolsCode"\
    "/postProcessCodeC++/testData/inferenceData"

modelPath = "/media/jose/6842930A30C05552/3Drecgonization/code/codeBackUp/toolsCode/"\
    "postProcessCodeC++/testData/model_data"

if __name__=="__main__":
    boxes_ = np.loadtxt(os.path.join(modelPath, 'boxes.txt')).reshape(-1, 7)
    scores_ = np.loadtxt(os.path.join(modelPath, 'scores.txt')).astype(int)
    labels_ = np.loadtxt(os.path.join(modelPath, 'labels.txt')).astype(int)
    
    visual_PC_and_3DBoxes(PC, boxes_, scores_, labels_)

    boxes_ = np.loadtxt(os.path.join(onnxpath, 'boxes.txt')).reshape(-1, 7)
    scores_ = np.loadtxt(os.path.join(onnxpath, 'scores.txt')).astype(int)
    labels_ = np.loadtxt(os.path.join(onnxpath, 'labels.txt')).astype(int)
    
    visual_PC_and_3DBoxes(PC, boxes_, scores_, labels_)



