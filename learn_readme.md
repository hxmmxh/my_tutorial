

# 目录
1. [文本](#文本)  
    1. [换行方法](#换行方法)
    2. [横线](#横线)
    3. [单行文本](#单行文本)
    4. [文本块](#文本块)
    5. [文字高亮](#文字高亮)
    6. [斜体,粗体,删除线][斜体粗体删除线]
2. [标题目录](#标题目录)
3. [链接](#链接)
4. [字体,颜色,大小](#字体/大小/颜色)


## 文本  
### 换行方法  

直接回车不能换行  
可以在上一行文本后面补两个空格  
这样下一行的文本就换行了  
或者就是在两行文本直接加一个空行。  

也能实现换行效果，不过这个行间距有点大。

### 横线

`三种方法，***，---，___`
***  
---
___

### 单行文本

    单行文本,在一行开头加入1个Tab或者4个空格。

### 文本块 

    方法一
    在连续几行的文本开头加入1个Tab或者4个空格
    欢迎到访    
    很高兴见到您
    祝您，早上好，中午好，下午好，晚安
    文本块内部换行可以直接回车

```
方法二
使用一对各三个的反引号
```

### 文字高亮  
能使行内部分文字高亮，使用一对反引号。

    `linux`   
    `网络编程`  
    `socket`   
    `epoll`   
实际显示效果如下  
`linux`   
`网络编程`  
`socket`   
`epoll` 


### 斜体,粗体,删除线  

*斜体1*    
_斜体2_  
**粗体1**  
__粗体2__  
这是一个 ~~删除线~~  
***斜粗体1***  
___斜粗体2___  
***~~斜粗体删除线1~~***  
~~***斜粗体删除线2***~~ 
```
总结
斜体用*或_
粗体用**或__
删除线用~~
上述三个格式可以组合
```

## 标题目录

```
# 一级目录
## 二级目录
### 三级目录
。。。#越多目录层次越低
```

## 链接

```diff
-锚点中如果存在空格，可用%20替换,存在失败风险`  
-最好用中文标点符号，否则可能失败`
+最好不使用标点，经测试在目录中存在空格或标点时，github无法跳转
```

## 字体/大小/颜色

[RGB颜色名对照表1](https://blog.csdn.net/heimu24/article/details/81192697)  
[RGB颜色名对照表2(更全)](http://tool.oschina.net/commons?type=3)


```
<font face="黑体">我是黑体字</font>  
<font face="微软雅黑">我是微软雅黑</font>  
<font face="STCAIYUN">我是华文彩云</font>  
<font color=red>我是红色</font>  
<font color=#008000>我是绿色</font>  
<font color=Blue>我是蓝色</font>  
<font size=5>我是尺寸</font>  
<font face="黑体" color=green size=5>我是黑体，绿色，尺寸为5</font>
```

**测试发现在github上修改失败**  
**但是在vscode预览上能够成功改变字体**
***
<font face="黑体">我是黑体字</font>  
<font face="微软雅黑">我是微软雅黑</font>  
<font face="STCAIYUN">我是华文彩云</font>  
<font color=red>我是红色</font>  
<font color=#008000>我是绿色</font>  
<font color=Blue>我是蓝色</font>  
<font size=5>我是尺寸</font>  
<font face="黑体" color=green size=5>我是黑体，绿色，尺寸为5</font>

***


[斜体粗体删除线]:#斜体,粗体,删除线