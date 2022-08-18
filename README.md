# Invoke-x64dbg-loaddll

调用x64dbg中的loadll.exe白加黑示例代码

在木马样本与杀毒软件的对抗中，再隐蔽的木马在被发现的那一刻，它的这一生就结束了。杀毒软件厂商通过SHA1/2、MD5等算法取得样本的唯一值来构建云端的特征库，当下一次攻击发生时，将会通过特征库进行比对，因此成本对抗不言而喻，红队的木马需要重新修改、编译，大大增加了对抗的时间、精力，这就是威胁情报的一种价值。反观有些软件确实会需要开发一些敏感行为的功能，如修改注册表、屏幕录像截图但这些是用户知情且授权的行为，这时杀毒软件再进行拦截的话，将大大降低软件使用的体验，所以出现了软件签名技术可以解决这类问题，当然软件签名技术不仅仅是为了只解决这一个问题而出现的。有些APT组织会通过控制软件开发商的代码仓库进行投毒或者通过入侵软件开发商来窃取签名，给自己的木马加上签名验证，杀毒软件遇到签名将会默认信任这个程序。但攻击软件开发商所需要投入的成本也相对比较高，telegram上也出现了花钱签名的服务，不过白嫖怪的数量可比金主爸爸要多，白嫖怪为了得到一个可以以签名程序运行自己任意代码的条件就会去挖掘一些软件厂商的程序是否存在DLL劫持漏洞，利用DLL劫持的特性达到披着羊皮的狼的目的。现阶段基本上大多数的APT组织在进行权限维持都会采用白加黑的技术来绕过杀毒软件的拦截和检测（特殊行为除外）。本文将会分享一个关于x64dbg这款调试工具的白加黑利用技巧。

参考阅读：[x64dbg中的白加黑利用](https://payloads.online/archivers/2022-08-17/1/)
