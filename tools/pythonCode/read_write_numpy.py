import numpy as np
import os


# readPath = './testData'
# name = "test"
# # numpy_file =  os.path.join(Path, name + ".npy")
# read_data = os.path.join(readPath, name + '.txt')
# datass = np.loadtxt('./testData/test.txt')
# print(datass)


data = np.array([1,2,3,4,5])
writePath = './testData/test.txt'
np.savetxt(writePath, data)
# np.save('./testData/test.npy', data)

def read_numpy_save_txt(numpyPath, txtPath):
    data = np.load(numpyPath)
    print(data.shape)
    np.savetxt(txtPath, data.flatten())

def transModelResult():
    read_mainPath = '/media/jose/6842930A30C05552/3Drecgonization/code/Transplantation_model/OpenPCDet_Train/Ztest/inferenceDatas'
    write_main_Path = '../../testData/model_data'

    name = '_hm'
    readPath = os.path.join(read_mainPath, name + '.npy')
    writePath = os.path.join(write_main_Path, name + '.txt')
    read_numpy_save_txt(readPath, writePath)

    name = '_center'
    readPath = os.path.join(read_mainPath, name + '.npy')
    writePath = os.path.join(write_main_Path, name + '.txt')
    read_numpy_save_txt(readPath, writePath)

    name = '_center_Z'
    readPath = os.path.join(read_mainPath, name + '.npy')
    writePath = os.path.join(write_main_Path, name + '.txt')
    read_numpy_save_txt(readPath, writePath)

    name = '_dim'
    readPath = os.path.join(read_mainPath, name + '.npy')
    writePath = os.path.join(write_main_Path, name + '.txt')
    read_numpy_save_txt(readPath, writePath)

    name = '_sin'
    readPath = os.path.join(read_mainPath, name + '.npy')
    writePath = os.path.join(write_main_Path, name + '.txt')
    read_numpy_save_txt(readPath, writePath)

    name = '_cos'
    readPath = os.path.join(read_mainPath, name + '.npy')
    writePath = os.path.join(write_main_Path, name + '.txt')
    read_numpy_save_txt(readPath, writePath)


def transONNXResult():
    read_mainPath = '/media/jose/6842930A30C05552/3Drecgonization/code/codeBackUp/RKNN/rknn-toolkit/examples/ZhouTest'
    write_main_Path = '../../testData/inferenceData'

    name = '_hm'
    readPath = os.path.join(read_mainPath, name + '.npy')
    writePath = os.path.join(write_main_Path, name + '.txt')
    read_numpy_save_txt(readPath, writePath)

    name = '_center'
    readPath = os.path.join(read_mainPath, name + '.npy')
    writePath = os.path.join(write_main_Path, name + '.txt')
    read_numpy_save_txt(readPath, writePath)

    name = '_center_Z'
    readPath = os.path.join(read_mainPath, name + '.npy')
    writePath = os.path.join(write_main_Path, name + '.txt')
    read_numpy_save_txt(readPath, writePath)

    name = '_dim'
    readPath = os.path.join(read_mainPath, name + '.npy')
    writePath = os.path.join(write_main_Path, name + '.txt')
    read_numpy_save_txt(readPath, writePath)

    name = '_sin'
    readPath = os.path.join(read_mainPath, name + '.npy')
    writePath = os.path.join(write_main_Path, name + '.txt')
    read_numpy_save_txt(readPath, writePath)

    name = '_cos'
    readPath = os.path.join(read_mainPath, name + '.npy')
    writePath = os.path.join(write_main_Path, name + '.txt')
    read_numpy_save_txt(readPath, writePath)


if __name__=="__main__":
    transModelResult()
    transONNXResult()




