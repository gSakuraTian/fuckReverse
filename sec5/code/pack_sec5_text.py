import re

def modify_hex_value(match):
    # 提取中间的三个字节并反转顺序
    byte1, byte2, byte3 = match.group(1), match.group(2), match.group(3)
    value = int(byte3 + byte2 + byte1, 16)
    
   
    if value > 0x400000:
        # 减去 79c 
        new_value = value - 1948
    else:
        
        new_value = value
    
    # 将新值转换回三个字节的格式，保持原始顺序
    new_byte1 = f"{(new_value & 0xFF):02X}"
    new_byte2 = f"{((new_value >> 8) & 0xFF):02X}"
    new_byte3 = f"{((new_value >> 16) & 0xFF):02X}"
    
    return f"01{new_byte1}{new_byte2}{new_byte3}00ffff"

def process_hex_data(hex_data):
    # 使用正则表达式查找所有匹配的模式
    pattern = r'01([\da-f]{2})([\da-f]{2})([\da-f]{2})00ffff'
    
    # 使用 re.sub 替换所有匹配
    return re.sub(pattern, modify_hex_value, hex_data)




# 读取第一个文件
with open('SEC5\CODE', 'rb') as f1:
    content1 = f1.read().hex()

# 读取第二个文件
with open('SEC5\output.txt', 'rb') as f2:
    content2 = f2.read().hex()

header = "ffff1b1c00000300ffff1b0300010125670000ffff"
footer = "1b1c00000300ffff1b030001012b6d0000ffff1b31"

# 将第二个文件的内容按照 '\n' 分割成列表
data2_list = content2.strip().split('0d0a5349474e0d0a')
i = 0
str = ""
while True:
    start = content1.find(header)
    if start == -1:
        str += content1
        break    
    
    start += len(header)
    end = content1.find(footer, start)
    if end == -1:
        str += content1
        break  
    str += content1[:start] + data2_list[i] + footer
    content1 = content1[end+len(footer):]
    i += 1



processed_hex_data = process_hex_data(str)

# 将结果写入新文件
with open('SEC5/new_CODE', 'wb') as f_out:
    f_out.write(bytes.fromhex(processed_hex_data))

print("处理完成，结果已写入 new_CODE")