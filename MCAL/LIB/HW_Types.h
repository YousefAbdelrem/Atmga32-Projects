/*
 * HW_Types.h
 *
 * Created: 11/7/2018 12:49:44 PM
 *  Author: AbdoMSpagh
 */ 


#ifndef HW_TYPES_H_
#define HW_TYPES_H_

 

 /*
static inline void   hw_write_reg  (v_uint8t* regAddr, uint8t val );
static inline uint8t hw_read_reg   (v_uint8t* regAddr  );

static inline void   hw_write_bit  (v_uint8t* regAddr,uint8t bit ,bool_t val );
static inline bool_t hw_read_bit   (v_uint8t* regAddr, uint8t bit );
static inline void   hw_write_bits (v_uint8t* regAddr, uint8t mask,  uint8t data );
static inline void   hw_set_bit  (v_uint8t* regAddr,uint8t bit );
static inline void   hw_clear_bit   (v_uint8t* regAddr, uint8t bit );

*/

#define bool_t uint8
/********************************************************
	* *
	* FUNCTION NAME: hw_write_reg
	* *
	* ARGUMENTS:
	*				pointer to reg
	*				val
	*				 
	*
	* NOTES :
	* *
	* RETURNS: * void
	* *
	*********************************************************/	
static inline void   hw_write_reg  (volatile uint8* regAddr,volatile uint8 val ){
	                 *((uint8*)(regAddr))=(val);
	
                     }

/********************************************************
	* *
	* FUNCTION NAME: hw_read_reg
	* *
	* ARGUMENTS:
	*				pointer to reg
	*				 
	*
	* NOTES :
	* *
	* RETURNS: * uint8t
	* *
	*********************************************************/	
static inline uint8 hw_read_reg   (volatile uint8* regAddr  ){
	                    return *((uint8*)(regAddr));
                     }
					 
	/********************************************************
	* *
	* FUNCTION NAME: hw_set_bit
	* *
	* ARGUMENTS:
	*				pointer to reg
	*				bit number
	*
	* NOTES :
	* *
	* RETURNS: * void
	* *
	*********************************************************/					 
static inline void   hw_set_bit  (volatile uint8* regAddr,volatile uint8 bit ){
	              *((uint8*)(regAddr))|=(1<<(bit));
	                
}

/********************************************************
* *
* FUNCTION NAME: hw_clear_bit
* *
* ARGUMENTS:
*				pointer to reg
*				bit number
*
* NOTES :
* *
* RETURNS: * void 
* *
*********************************************************/
static inline void   hw_clear_bit   (volatile uint8* regAddr,volatile uint8 bit ){
	 	              *((uint8*)(regAddr))&=~(1<<(bit));               
}
/********************************************************
* *
* FUNCTION NAME: hw_read_bit
* *
* ARGUMENTS:
*				pointer to reg
*				bit number
*				 
* NOTES :  
* *
* RETURNS: * bool_t 
* *
*********************************************************/
static inline bool_t hw_read_bit   (volatile uint8* regAddr, volatile uint8 bit ){
		 	             return (*((uint8*)(regAddr))&(1<<(bit)))>>(bit);

}

/********************************************************
* *
* FUNCTION NAME: hw_write_bit
* *
* ARGUMENTS:
*				pointer to reg
*				bit number
*				value
* NOTES : value should in range of 0:1
* *
* RETURNS: * void
* *
*********************************************************/
static inline void   hw_write_bit  (volatile uint8* regAddr,volatile uint8 bit ,bool_t val ){
                 	if ((val)&0x1)
                 	{
						 hw_set_bit((regAddr),(bit));
                 	} 
                 	else 
                 	{
						 hw_clear_bit((regAddr),(bit));
						 
                 	}
	
}
/********************************************************
* *
* FUNCTION NAME: hw_write_bits
* *
* ARGUMENTS:
*				pointer to reg
*				mask
*				value
* NOTES : value should in range of 0:1
* *
* RETURNS: * void
* *
*********************************************************/
static inline void   hw_write_bits (volatile uint8* regAddr,volatile uint8 mask,  uint8 val ){
	
	    
	  *((uint8*)(regAddr))|=((mask) & (val));  /// set ones 
	  *((uint8*)(regAddr))&=~((mask )& (~(val)));  // clear zeros 
}



 
#endif /* HW_TYPES_H_ */
