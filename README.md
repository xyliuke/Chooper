# 音视频学习
这是一个自学音视频的学习笔记，按照自己理解的方式来学习。

## 配置环境
现在使用的开发环境是：Mac+CLion+CMake, OpenGL使用的glew库，使用GLFW作为UI框架，测试框架使用的是Catch2。
### CMake的配置
CMake是按照各个目录下有一个CMakeLists.txt的方式来组织，具体使用方式网上有很多教程。也可以参考这个Demo中的组织方式，
我也是在学习中，不一定是最正确的方式。
### 创建一个简单的OpenGL例子
这里主要是参考了Learn OpenGL的文档，链接：
https://learnopengl-cn.github.io/intro/
当前Demo中，使用了glew库和GLFW库，在src/gl/triangle类中，有个简单的三角形绘制功能，对Learn OpenGL文档中的Demo进行了修改，可以参考下。
基本的步骤是：
* 初始化GLFW窗口
* 初始化OpenGL环境
* 编译顶点着色器和片段着色器
* 绘制三角形
* 在GLFW中循环调用绘制

### 创建纹理
纹理就是在一个图形上添加贴图。这里使用了stb_image，这是个跨平台的图片库，也是Learn OpenGL教程中使用的。
本来我是想使用系统的图片库来解码，后发现还是stb_image简单好用。纹理使用成功后，就真实渲染一帧视频帧，使用的
是RGB格式的视频图片，图形的范围是整个窗口大小，这样看起来像是播放器在运行。

## 封装一些常用类
主要是对一些常用的功能进行了封装，不一定很合理，但是能run。封装的类主要有：
* 文件读取
* shader使用
* 纹理
* 图片解码
* 窗口
* 线程

## 渲染视频图片
### 视频转成图片
使用FFmpeg命令，读取每一帧生成一组jpeg图片
```shell
ffmpeg -i test.mp4 -r 30 -f image2 foo-%05d.jpeg
```
其中test.mp4是视频文件，生成后的图片命名规则是foo-00001.jpeg、foo-00002.jpeg等

### 显示基本图片序列
首先需要能显示最基本的图片序列，来保证显示正确。
在GLFW渲染的循环中，按照顺序依次调用图片作为纹理，为了显示速度正常，可以简化为3次循环（约20帧/秒）更新一张图片。基本代码
为：
```objectivec
w->set_loop_callback([=] mutable {
    if (count % 3 == 0) {
        std::stringstream ss;
        ss << "../test/resource/image_group/foo-";
        ss << std::setw(5) << std::setfill('0') << count;
        ss << ".jpeg";
        v->update(ss.str());
        v->render();
    } else {
        v->render();
    }
    count += 1; 
});
```

### 优化解码性能
在能正常显示图片序列后，应该把图片解码放在非主线程中运行，这就涉及到两个问题，一是创建一个非主线程的timer，另一个是要能切换到主线程运行。创建timer类，使用了boost库中的steady_timer类实现的，具体可能参考time/timer类的实现。同时将timer中的任务放在新创建的线程中执行。

另一个问题是切换主线程问题，这个问题困扰了一段时间。因为一般iOS、Mac、Android开发不需要考虑这个问题，而C++本身也没有切换主线程的功能。后才想到这个功能其实很简单，大致思路就是先创建一个队列，在非主线程中，将一个任务（function对象）保存到这个队列的栈底，再在主线程的循环中调用这个栈顶的第一个任务，并通过锁来同步对队列的操作。具体代码可参考time/thread_util该类。

### 等比例显示
现在显示的视频图片还是全屏的，主要是因为四边形的坐标你也别是：左上(-1, 1)、左下（-1，-1），右上（1，1），右下（1，-1）。而如果想在等比例显示，就需要将宽度对齐，高度自适应。思路是首先获取到图片的高度和宽度，计算出图片宽高比例和窗口宽高比例，再将四边形的y轴修改即可。具体代码为：
```objectivec
void ResizeTexture(int window_width, int window_height) {
    if (height > 0 && width > 0) {
        float ly = 1.f;
        float ry = -1.f;
        int should_height = int(float(height * window_width) / float(width));
        ly = float(should_height) / float(window_height);
        ry = -ly;
        render->UpdateSize(-1.f, ly, 1.f, ry, 0, 1);
    }
}
```

