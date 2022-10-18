#使用opencv识别能量机关

##使用说明
--将视频文件名称写在capture.open()中，运行后进行识别

###识别思路
####识别能量机关
-分离通道进行二值化
-使用开运算使图像更明显
-使用水满法是锤子状和宝剑状区别更明显
-使用闭运算，再使用findCountours，进行范围限制找出装甲板轮廓
-进行二值化和膨胀使中心更明显
-使用findCountours和面积限制选出中心
####测量距离和角度
-由内参矩阵得出焦距
-由识别结果计算装甲板的像素宽度
-由相似三角形原理计算距离
-识别已经得出边缘矩形和中心矩形，求出中心点
-通过三角关系和tan、ractan函数其求得角度