#include "key.h"

struct 
{
    uint16_t value;  ///<键值
    uint16_t status; ///按键状态队列
}key;	//结构体

/*
描述:读取按下的键值
返回值:返回的值范围为0~16
*/
uint8_t ReadKeyValue(void)
{
    uint8_t position;
    
    for(position = 0; position <16; position++)
    {
        if((key.value>>position)&0x01 == 1)
            break;
    }
    
    /*键值不在范围内*/
    if(position++ == 16)
        position = 0;
    
    return position; 
}

/*防止代码优化*/
static void _line_write(uint8_t position)
{
    /*行定位, 拉低对应引脚,拉高其他引脚避免影响*/
    P2 = ~(0x80>>(position / 4));		
}

/*防止代码优化*/
static uint8_t _list_read(uint8_t position)
{
    position = position % 4;
    
    switch(position)
    {
        case 0: return P20;
        case 1: return P21;
        case 2: return P22;
        case 3: return P23;
    }
    
    return 1;
}

/*单按键扫描, 0~15*/
static void _key_scan_once(uint8_t position)
{
    uint8_t buff_P2 = P2;
    DISLED;
    
    /*拉低按键对应行*/
    _line_write(position);
    if(_list_read(position) == 0)   ///<检测状态
		key.status |= 1;
    
    /*恢复数据并避免数码管和138的冲突*/
    P2 = buff_P2|0xf0;
    ENLED;
}

/*矩阵按键扫描*/
void KeyScan(void)
{
    static uint8_t key_count = 0;
    uint16_t buff_status = key.status;
    
    /*获取按键上一次检测的结果*/
    key.status <<= 1;
    buff_status >>= 15;
    
    //if(key_count == 0)        ///<备注此行则为矩阵按键 单按键只做测试,如果需要多功能请自行修改
    _key_scan_once(key_count);  ///<检测按键
    
    /*存储键值*/
    if(buff_status & 0x01 == key.status & 0x01)
        key.value = 0x01 << key_count;
    
    if(key_count++ == 15)
        key_count = 0;
}

