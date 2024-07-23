import codecs

def extract_data(content, header, footer):
    
    while True:
        str = ""
        start = content.find(header)
        if start == -1:
            return None    
    
        start += len(header)
        end = content.find(footer, start)
        if end == -1:
            return None    
        
        byte_data = codecs.decode(content[start:end], 'hex')
        # 解码为 Shift-JIS 编码的字符串 shift_jis
        str +=  byte_data.decode('shift_jis', errors='ignore')
        #数据间隔标志
        str += "\nSIGN\n"
        content = content[end+len(footer):]

        # 指定要写入的文件路径
        file_path = "SEC5\output.txt"
        
        with open(file_path, 'a+', encoding='shift_jis') as f:
            f.write(str)
    

# 读取文件
filename = "SEC5\CODE"  
try:
    with open(filename, "rb") as file:
        content = file.read().hex()
except IOError:
    print("无法打开文件")
    exit(1)

# 定义头部和尾部
header = "ffff1b1c00000300ffff1b0300010125670000ffff"
footer = "1b1c00000300ffff1b030001012b6d0000ffff1b31"

# 提取数据
extract_data(content, header, footer)
