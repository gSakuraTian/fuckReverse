### 解包ロケットの夏～Full Voice Version～

读取2个dword 文件头进行判断

第二个dword ？

第三个  dword 为文件数 做为文件读取数据 循环判断



![image-20240720160435009](packdat.assets/image-20240720160435009.png)



![image-20240720160518062](packdat.assets/image-20240720160518062.png)

![image-20240720161123993](packdat.assets/image-20240720161123993.png)

文件名相同则跳出文件读取循环

![image-20240720161721809](packdat.assets/image-20240720161721809.png)

将E02E90作为偏移

30010000作为判断 

将67236作为读取字节数

![image-20240721154919285](packdat.assets/image-20240721154919285.png)

开辟空间 读取数据

![image-20240721154901333](packdat.assets/image-20240721154901333.png)

对数据进行操作

![image-20240721155035647](packdat.assets/image-20240721155035647.png)

解密数据 获取文件



————————————————



![image-20240721161422498](packdat.assets/image-20240721161422498.png)

![image-20240721163242983](packdat.assets/image-20240721163242983.png)



![image-20240721165144323](packdat.assets/image-20240721165144323.png)

最后数据结构存储为

![image-20240721170324465](packdat.assets/image-20240721170324465.png)

![image-20240721170533396](packdat.assets/image-20240721170533396.png)

![image-20240721171802771](packdat.assets/image-20240721171802771.png)

从后往前copy