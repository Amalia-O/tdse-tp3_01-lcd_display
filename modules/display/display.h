//=====[#include guards - begin]===============================================

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

//=====[Declaration of public defines]=========================================
#include <stdint.h>
#include <stdio.h>
#define TEST_0 (0)
#define TEST_1 (1)
#define TEST_2 (2)

/*  {I2C,   4BITS,  8BITS}
    {0,     1,      2}
*/

#define TEST_X (TEST_0)
#define SYSTEM_TIME_INCREMENT_MS   10
#define DISPLAY_REFRESH_TIME_MS 1000

// Functional states
#ifndef OFF
#define OFF    0
#endif
#ifndef ON
#define ON     (!OFF)
#endif

// Electrical states
#ifndef LOW
#define LOW    0
#endif
#ifndef HIGH
#define HIGH   (!LOW)
#endif

#define delay(ms)      thread_sleep_for( ms )


//=====[Declaration of public data types]======================================

typedef enum {
     DISPLAY_CONNECTION_GPIO_4BITS,
     DISPLAY_CONNECTION_GPIO_8BITS,
     DISPLAY_CONNECTION_I2C_PCF8574_IO_EXPANDER,
} displayConnection_t;

typedef struct {
   displayConnection_t connection;                                                 
} display_t;

//=====[Declarations (prototypes) of public functions]=========================

void displayInit( displayConnection_t connection );
 
void displayCharPositionWrite( uint8_t charPositionX, uint8_t charPositionY );

void displayStringWrite( const char * str );

static uint32_t contador =0;

inline static void DisplayInit(){
    contador = 0;
    //aca hay que hacer la copilacion condiiconal para modificar los bits
    #if (TEST_X == TEST_0)
        displayInit( DISPLAY_CONNECTION_I2C_PCF8574_IO_EXPANDER );
    #endif

    #if ( TEST_X == TEST_1 )
        displayInit( DISPLAY_CONNECTION_GPIO_4BITS );
    #endif

    #if (TEST_X == TEST_2)
        displayInit( DISPLAY_CONNECTION_GPIO_8BITS );
    #endif
    
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Temperature:" );
}


inline static void DisplayUpdate()
{
    static int accumulatedDisplayTime = 0;
    char temperatureString[3] = "";
    
    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;

        sprintf(temperatureString, "%.0d", contador++);
        displayCharPositionWrite ( 12,0 );
        displayStringWrite( temperatureString );
        displayCharPositionWrite ( 14,0 );
        displayStringWrite( "'C" );

    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    }
    
}

//=====[#include guards - end]=================================================

#endif // _DISPLAY_H_