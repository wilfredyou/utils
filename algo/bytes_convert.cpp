uint32 Reverse32(uint32 x)
{
    return ((x&0x000000ff)<<24)|((x&0x0000ff00)<<8)|
		   ((x&0x00ff0000)>>8)|((x&0xff000000)>>24);
}

uint32 Reverse32(uint32 x)
{
        int i;
        char *temp[4];
        for(i = 0;i < 4;i++){
                temp[i] = (char*)(&x) + i;
        }   
        return ((*temp[3]<<24)|(*temp[2]<<16)|(*temp[1]<<8)|*temp[0]);
} 

uint32 dev_to_cpu(uint32 data)
{
     unsigned int x = 1;
     if(*(char *)&x == 1)
         return data;//Little-Endian
     else
         return Reverse32(data);//Big-Endian 
}


