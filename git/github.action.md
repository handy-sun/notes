## 问题： 发布release时，action日志提示访问失败（返回403之类的）

这种情况是action没有仓库写权限导致的

正确解决办法：

在你的仓库页面，注意是仓库页面的setting里面：

Actions=> General=>Workflow permisssion=> Read and Write permissions
