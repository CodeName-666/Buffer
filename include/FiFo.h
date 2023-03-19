/*
 * FIFO.h
 *
 * Created: 08.03.2016 18:39:52
 *  Author: AP
 */


#ifndef FIFO_H_
#define FIFO_H_

#include "stdint.h"


#define FIFO_N_OK                        0
#define FIFO_OK                          1

typedef uint8_t FIFO_Return_t;

#define FIFO_CALCULATE_BUFFERSIZE(bufferQuantity, bufferType)        \
        (bufferQuantity * sizeof(bufferType))

/**
 *
 */
#define FIFO_IS_BUFFER_READY(bufPtr)                            \
          ((bufPtr.status == FIFO_BUFFER_EMPTY) ||                       \
           (bufPtr.status == FIFO_BUFFER_DATA_AVAILABLE) ||              \
           (bufPtr.status == FIFO_BUFFER_FULL))
/**
 *
 */
#define FIFO_HAS_BUFFER_ERRORS(bufPtr)                           \
        ((bufPtr.status == FIFO_WRITE_OVERFLOW_ERROR) ||        \
         (bufPtr.status == FIFO_UNDEF_ERROR))
/**
 *
 */
#define FIFO_IS_BUFFER_FULL(bufPtr)                             \
        (bufPtr.status == FIFO_BUFFER_FULL)

/**
 *
 */
#define FIFO_IS_BUFFER_EMPTY(bufPtr)                            \
        (bufPtr.status == FIFO_BUFFER_EMPTY)

/**
 *
 */
#define FIFO_GET_WRITE_COUNT(bufPtr)               \
      (bufPtr.counter.write)

/**
 *
 */
#define FIFO_GET_READ_COUNT(bufPtr)                \
      (bufPtr.counter.read)

/**
 *
 */
#define FIFO_GET_BUFFER_SIZE(bufPtr)               \
      (bufPtr.bufferSize)

/**
 *
 */
#define FIFO_SET_WRITE_BUFFER(bufPtr,val)          \
      (bufPtr.counter.write = val)

/**
 *
 */
#define FIFO_SET_READ_BUFFER(bufPtr,val)           \
      (bufPtr.counter.read = val)

/**
 *
 */
#define FIFO_READ(bufPtr,index)         \
      (bufPtr.bufferPtr[index])

/**
 *
 */
#define FIFO_WRITE(bufPtr,index, param)   \
      (bufPtr.bufferPtr[index] = param)

/**
 *
 */
#define FIFO_GET_OVERFLOW_STATUS(bufPtr)           \
        (bufPtr.counter.overflow)
/**
 *
 */
#define FIFO_SET_OVERFLOW_STATUS(bufPtr, stat)     \
        (bufPtr.counter.overflow = stat)
/**
 *
 */
#define FIFO_SET_BUFFER_STATUS(bufPtr, stat)       \
        (bufPtr.status = stat)
/**
 *
 */
#define FIFO_GET_BUFFER_STATUS(bufPtr)             \
        (bufPtr.status)
/**
 * @brief Buffer Status
 *
 * Status values which the FIFO can contains.
 */
enum FIFO_BufferStatus_e
{
   FIFO_BUFFER_EMPTY = 0x00,
   FIFO_BUFFER_DATA_AVAILABLE,
   FIFO_BUFFER_FULL,
   FIFO_WRITE_OVERFLOW_ERROR,
   FIFO_UNDEF_ERROR,
   FIFO_NO_INIT,
};

/**
 * @brief FiFo Counter
 *
 * Structure which contains all needed counter parameter to handle the
 * FIFO Buffer. This counter represents the read/write position.
 * To calculate the correct position, the overflow parameter is needed.
 */
typedef struct
{
   uint16_t read;
   uint16_t write;
   bool overflow;
   
} FIFO_Counter_t;

/**
 * @brief Buffer Structure
 *
 * This struct represents a FIFO Buffer.
 */
typedef struct
{
   uint8_t *bufferPtr;
   uint16_t bufferSize;
   FIFO_BufferStatus_e status;
   FIFO_Counter_t counter;
} FIFO_Buffer_t;



template<typename FiFoType> class FiFo
{

   public:
    


   protected:

      /**
       * @brief Increment FIFO Write Counter
       */
      void incrementWriteCounter(void);

      /**
       * @brief Increment FIFO Read Counter
       */
      void incrementReadCounter(void);

      /**
       * @brief Update FIFO Buffer Status
       */
      void updateBufferStatus(void);

   public:
      /**
       * @brief FIFO Constructor
       */
      FiFo();
      /**
       *  @brief Init FIFO Buffer
       *
       *  @param [in] avBuffer Parameter_Description
       *  @param [in] avSize Parameter_Description
       *  @return Return_Description
       *
       *  @details Details
       */
      void initBuffer(uint8_t* avBuffer, uint16_t avSize);

      /**
       *  @brief Write Into FIFO
       *
       *  @param [in] p Parameter_Description
       *  @return Return_Description
       *
       *  @details Details
       */
      bool write(FiFoType* p);

      /**
       *  @brief Write Into FIFO
       *
       *  @param [in] p Parameter_Description
       *  @param [in] length size of the parameter
       *  @param [in] typeSize size of the FiFoType. if p is not an default type like unit<x>_t,
       *  the size of this type can be set with this parameter.
       *  @return Return_Description
       *
       *  @details Details
       */
      bool write(FiFoType* p, uint16_t length, uint16_t typeSize = 1);

      /**
       *  @brief Read From FIFO
       *
       *  @return Return_Description
       *
       *  @details Details
       */
      FiFoType read(void);

      /**
       *  @brief Get FIFO Buffer Status
       *
       *  @return Return_Description
       *
       *  @details Details
       */
      uint16_t getBufferStatus(void);

      /**
       *  @brief Get Free FIFO Buffer Space
       *
       *  @return Return_Description
       *
       *  @details Details
       */
      uint16_t getFreeBufferSpace(void);

      /**
       * @brief Has FIFO Data To Read
       *
       * @details Details
       */
      bool dataAvailable(void);


      uint16_t getUsedBufferSize(void);

      uint16_t getSizeOfBuffer(void);

   private:
      FIFO_Buffer_t m_buffer;
};

/**************************************************************************************************
 * FUNCTION: FiFo(...)
 *************************************************************************************************/
template<typename FiFoType> inline FiFo<FiFoType>::FiFo()
{
   m_buffer.bufferPtr = NULL;
   m_buffer.bufferSize = 0;
   m_buffer.counter.overflow = false;
   m_buffer.counter.read = 0u;
   m_buffer.counter.write = 0u;
   m_buffer.status = FIFO_NO_INIT;

}

/**************************************************************************************************
 * FUNCTION: void FIOF_InitBuffer(...)
 *************************************************************************************************/
template<typename FiFoType> inline void FiFo<FiFoType>::initBuffer(uint8_t *avBuffer,
         uint16_t avSize)
{
   if (avBuffer != NULL)
   {
      m_buffer.bufferPtr = avBuffer;
      m_buffer.bufferSize = avSize;
      m_buffer.status = FIFO_BUFFER_EMPTY;
      m_buffer.counter.overflow = false;
      m_buffer.counter.read = 0u;
      m_buffer.counter.write = 0u;
   }
   else
   {
      m_buffer.bufferPtr = NULL;
   }
   return;
}

/**************************************************************************************************
 * FUNCTION: void FIFO_Write(...)
 *************************************************************************************************/
template<typename FiFoType> inline bool FiFo<FiFoType>::write(FiFoType* p)
{
   uint16_t i;
   uint8_t count;
   bool status = false;
   uint8_t* data;

   if (FIFO_IS_BUFFER_READY(m_buffer) == true)
   {
      data = (uint8_t*) p;
      for (count = 0; count < sizeof(FiFoType); count++)
      {
         i = FIFO_GET_WRITE_COUNT(m_buffer);
         FIFO_WRITE(m_buffer, i, data[count]);
         incrementWriteCounter();
         updateBufferStatus();
      }

      status = true;
   }
   return status;
}


/**************************************************************************************************
 * FUNCTION: void FIFO_Write(...)
 *************************************************************************************************/
template<typename FiFoType> inline bool FiFo<FiFoType>::write(FiFoType* p, uint16_t length, uint16_t typeSize)
{
   uint16_t i;
   uint8_t count;
   bool status = false;
   uint8_t* data;

   if (FIFO_IS_BUFFER_READY(m_buffer) == true)
   {
	  data = (uint8_t*) p;

	  Serial.print("DataLen = "); Serial.println(typeSize * length);
	  Serial.print("Data = ");
	  for (count = 0; count < (typeSize * length); count++)
	  {
		 Serial.print((char)data[count]);
		 i = FIFO_GET_WRITE_COUNT(m_buffer);
		 FIFO_WRITE(m_buffer, i, data[count]);
		 incrementWriteCounter();
		 updateBufferStatus();
	  }

	  status = true;
   }
   return status;
}


/**************************************************************************************************
 * FUNCTION: char FIFO_Read(...)
 *************************************************************************************************/
template<typename FiFoType> inline FiFoType FiFo<FiFoType>::read(void)
{
   uint8_t p[sizeof(FiFoType)] = {0};
   FiFoType* ret = NULL;
   uint16_t i;
   uint8_t count;
   if (FIFO_IS_BUFFER_READY(m_buffer) == true &&
   FIFO_IS_BUFFER_EMPTY(m_buffer) == false)
   {
      for (count = 0; count < sizeof(FiFoType); count++)
      {
         i = FIFO_GET_READ_COUNT(m_buffer);
         p[count] = FIFO_READ(m_buffer, i);
         incrementReadCounter();
         updateBufferStatus();
      }
   }

   ret = (FiFoType*) p;
   return *ret;
}

/**************************************************************************************************
 * FUNCTION: void FIFO_IncrementWriteCounter(...)
 *************************************************************************************************/
template<typename FiFoType> inline void FiFo<FiFoType>::incrementWriteCounter(void)
{
   uint8_t size;

   size = FIFO_GET_WRITE_COUNT(m_buffer) + 1;
   if(size > FIFO_GET_BUFFER_SIZE(m_buffer))
   {
      size = 0;
      FIFO_SET_OVERFLOW_STATUS(m_buffer, true);
   }

   FIFO_SET_WRITE_BUFFER(m_buffer, size);
   return;
}

/**************************************************************************************************
 * FUNCTION: void FIFO_IncrementReadCounter(...)
 *************************************************************************************************/
template<typename FiFoType> inline void FiFo<FiFoType>::incrementReadCounter(void)
{
   uint8_t size;

   size = FIFO_GET_READ_COUNT(m_buffer) + 1;
   if(size > FIFO_GET_BUFFER_SIZE(m_buffer))
   {
      size = 0;
      FIFO_SET_OVERFLOW_STATUS(m_buffer, false);
   }

   FIFO_SET_READ_BUFFER(m_buffer, size);
   return;
}

/**************************************************************************************************
 * FUNCTION: void FIFO_UpdateBufferStatus(...)
 *************************************************************************************************/
template<typename FiFoType> inline void FiFo<FiFoType>::updateBufferStatus(void)
{
   /************************************************************************
    *
    *     Overflow = FALSE
    * |--------------------------------------------------------|
    *                   ^                        ^
    *                   a                        b
    *
    *                   b > a --- OK Daten Verf�gbar
    *                   b = a --- OK Keine Daten verf�bar
    *                   b < a --- kein error muss abgesichert werden
    *
    *     Overflow = TRUE
    *  |--------------------------------------------------------|
    *              ^                        ^
    *              b                        a
    *
    *
    *              b < a --- OK
    *               b = a --- Buffer voll
    *              b > a --- Error Write Overflow
    *
    ************************************************************************/
   boolean o;
   uint8_t w, r;
   w = FIFO_GET_WRITE_COUNT(m_buffer);
   r = FIFO_GET_READ_COUNT(m_buffer);
   o = (boolean) FIFO_GET_OVERFLOW_STATUS(m_buffer);

   if (o == false)
   {
      if (w > r)
      {
         FIFO_SET_BUFFER_STATUS(m_buffer, FIFO_BUFFER_DATA_AVAILABLE);
      }
      else if (w == r)
      {
         FIFO_SET_BUFFER_STATUS(m_buffer, FIFO_BUFFER_EMPTY);
      }
      else
      {
         FIFO_SET_BUFFER_STATUS(m_buffer, FIFO_UNDEF_ERROR);
      }
   }
   else
   {
      if (w > r)
      {
         FIFO_SET_BUFFER_STATUS(m_buffer, FIFO_WRITE_OVERFLOW_ERROR);
      }
      else if (w == r)
      {
         FIFO_SET_BUFFER_STATUS(m_buffer, FIFO_BUFFER_FULL);
      }
      else
      {
         FIFO_SET_BUFFER_STATUS(m_buffer, FIFO_BUFFER_DATA_AVAILABLE);
      }
   }
   return;
}

/**************************************************************************************************
 * FUNCTION: FIFO_BufferStatus_e FIFO_GetBufferStatus(...)
 *************************************************************************************************/
template<typename FiFoType> inline uint16_t FiFo<FiFoType>::getBufferStatus(void)
{
   return FIFO_GET_BUFFER_STATUS(m_buffer);
}

/**************************************************************************************************
 * FUNCTION: uint16_t FIFO_GetFreeBufferSpace(...)
 *************************************************************************************************/
template<typename FiFoType> inline uint16_t FiFo<FiFoType>::getFreeBufferSpace(void)
{
   boolean o;
   uint8_t w, r;
   uint16_t space = 0;
   w = FIFO_GET_WRITE_COUNT(m_buffer);
   r = FIFO_GET_READ_COUNT(m_buffer);
   o = (boolean) FIFO_GET_OVERFLOW_STATUS(m_buffer);

   if (o == true)
   {
      space = FIFO_GET_BUFFER_SIZE(m_buffer) - (r - w);
   }
   else
   {
      space = FIFO_GET_BUFFER_SIZE(m_buffer) - (w - r);
   }
   return space;
}

/**************************************************************************************************
 * FUNCTION: uint16_t DataAvailable(...)
 *************************************************************************************************/
template<typename FiFoType>
inline bool FiFo<FiFoType>::dataAvailable(void)
{
   bool ret = false;

   if (FIFO_IS_BUFFER_READY(m_buffer) == true &&
   FIFO_IS_BUFFER_EMPTY(m_buffer) == false)
   {
      ret = true;
   }

   return ret;
}


template<typename FiFoType> inline uint16_t FiFo<FiFoType>::getSizeOfBuffer(void)
{
	return FIFO_GET_BUFFER_SIZE(m_buffer);
}

template<typename FiFoType> inline uint16_t FiFo<FiFoType>::getUsedBufferSize(void)
{
	return getSizeOfBuffer() - getFreeBufferSpace() + 1;
}

#endif /* FIFO_H_ */
