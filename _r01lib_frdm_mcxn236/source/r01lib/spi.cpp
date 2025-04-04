/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license License
 */

extern "C" {
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_lpspi.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
}

#include	"io.h"
#include	"spi.h"


#ifdef	CPU_MCXN947VDF
	#define EXAMPLE_LPSPI_MASTER_BASEADDR (LPSPI1)
	#define EXAMPLE_LPSPI_MASTER_PCS_FOR_INIT     (kLPSPI_Pcs0)
	#define EXAMPLE_LPSPI_MASTER_PCS_FOR_TRANSFER (kLPSPI_MasterPcs0)
	#define LPSPI_MASTER_CLK_FREQ CLOCK_GetLPFlexCommClkFreq(1u)
	#define TRANSFER_SIZE     64U     /*! Transfer dataSize */
	#define TRANSFER_BAUDRATE 500000U /*! Transfer baudrate - 500k */
#elif	CPU_MCXN236VDF
	#define EXAMPLE_LPSPI_MASTER_BASEADDR (LPSPI3)
	#define EXAMPLE_LPSPI_MASTER_PCS_FOR_INIT     (kLPSPI_Pcs0)
	#define EXAMPLE_LPSPI_MASTER_PCS_FOR_TRANSFER (kLPSPI_MasterPcs0)
	#define LPSPI_MASTER_CLK_FREQ CLOCK_GetLPFlexCommClkFreq(3u)
	#define TRANSFER_SIZE     64U     /*! Transfer dataSize */
	#define TRANSFER_BAUDRATE 500000U /*! Transfer baudrate - 500k */
#elif	CPU_MCXA156VLL
	#if 1	//	to use MikroBus connector
		#define EXAMPLE_LPSPI_MASTER_BASEADDR         (LPSPI0)
		#define EXAMPLE_LPSPI_MASTER_IRQN             (LPSPI0_IRQn)
		#define EXAMPLE_LPSPI_DEALY_COUNT             0xFFFFF
		#define LPSPI_MASTER_CLK_FREQ                 (CLOCK_GetLpspiClkFreq(0))
		#define EXAMPLE_LPSPI_MASTER_PCS_FOR_INIT     (kLPSPI_Pcs0)
		#define EXAMPLE_LPSPI_MASTER_PCS_FOR_TRANSFER (kLPSPI_MasterPcs0)
		#define EXAMPLE_LPSPI_MASTER_IRQHandler       (LPSPI0_IRQHandler)
		#define TRANSFER_SIZE     64U     /*! Transfer dataSize */
		#define TRANSFER_BAUDRATE 500000U /*! Transfer baudrate - 500k */
	#else	//	SPI0 is not routed to Arduino shield connector
		#define EXAMPLE_LPSPI_MASTER_BASEADDR         (LPSPI1)
		#define EXAMPLE_LPSPI_MASTER_IRQN             (LPSPI1_IRQn)
		#define EXAMPLE_LPSPI_DEALY_COUNT             0xFFFFF
		#define LPSPI_MASTER_CLK_FREQ                 (CLOCK_GetLpspiClkFreq(1))
		#define EXAMPLE_LPSPI_MASTER_PCS_FOR_INIT     (kLPSPI_Pcs1)
		#define EXAMPLE_LPSPI_MASTER_PCS_FOR_TRANSFER (kLPSPI_MasterPcs1)
		#define EXAMPLE_LPSPI_MASTER_IRQHandler       (LPSPI1_IRQHandler)
		#define TRANSFER_SIZE     64U     /*! Transfer dataSize */
		#define TRANSFER_BAUDRATE 500000U /*! Transfer baudrate - 500k */
	#endif
#elif	CPU_MCXA153VLH
	#define EXAMPLE_LPSPI_MASTER_BASEADDR         (LPSPI1)
	#define EXAMPLE_LPSPI_MASTER_IRQN             (LPSPI1_IRQn)
	#define EXAMPLE_LPSPI_DEALY_COUNT             0xFFFFF
	#define LPSPI_MASTER_CLK_FREQ                 (CLOCK_GetLpspiClkFreq(1))
	#define EXAMPLE_LPSPI_MASTER_PCS_FOR_INIT     (kLPSPI_Pcs1)
	#define EXAMPLE_LPSPI_MASTER_PCS_FOR_TRANSFER (kLPSPI_MasterPcs1)
	#define EXAMPLE_LPSPI_MASTER_IRQHandler       (LPSPI1_IRQHandler)
	#define TRANSFER_SIZE     64U     /*! Transfer dataSize */
	#define TRANSFER_BAUDRATE 500000U /*! Transfer baudrate - 500k */
#else
	#error Not supported CPU
#endif

SPI::SPI( int mosi, int miso, int sclk, int cs ) : Obj( true )
{
#ifdef	CPU_MCXN947VDF
#elif	CPU_MCXN236VDF
#elif	CPU_MCXA156VLL
#elif	CPU_MCXA153VLH
	RESET_ReleasePeripheralReset( kLPSPI1_RST_SHIFT_RSTn );
#else
#endif

	LPSPI_MasterGetDefaultConfig( &masterConfig );
	
	masterConfig.whichPcs = EXAMPLE_LPSPI_MASTER_PCS_FOR_INIT;
	masterConfig.pcsToSckDelayInNanoSec        = 1000000000U / (masterConfig.baudRate * 2U);
	masterConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / (masterConfig.baudRate * 2U);
	masterConfig.betweenTransferDelayInNanoSec = 1000000000U / (masterConfig.baudRate * 2U);

	LPSPI_MasterInit( EXAMPLE_LPSPI_MASTER_BASEADDR, &masterConfig, LPSPI_MASTER_CLK_FREQ );

	frequency( SPI_FREQ );
	mode( 0 );

	//	pin enable
	
	DigitalInOut	_cs(   cs   );
	DigitalInOut	_mosi( mosi );
	DigitalInOut	_miso( miso );
	DigitalInOut	_sclk( sclk );

#ifdef	CPU_MCXN947VDF
	_mosi.pin_mux( 2 );
	_sclk.pin_mux( 2 );
	_miso.pin_mux( 2 );
	_cs.pin_mux(   2 );
#elif	CPU_MCXN236VDF
	_mosi.pin_mux( 2 );
	_sclk.pin_mux( 2 );
	_miso.pin_mux( 2 );
	_cs.pin_mux(   2 );
#elif	CPU_MCXA156VLL
	_sclk.pin_mux( 2 );
	_mosi.pin_mux( 2 );
	_miso.pin_mux( 2 );
	_cs.pin_mux(   2 );
#elif	CPU_MCXA153VLH
	_sclk.pin_mux( 2 );
	_mosi.pin_mux( 2 );
	_miso.pin_mux( 2 );
	_cs.pin_mux(   2 );
#else
	#error Not supported CPU
#endif
}

SPI::~SPI()
{
	LPSPI_Deinit( EXAMPLE_LPSPI_MASTER_BASEADDR );
}

void SPI::frequency( uint32_t frequency )
{
	masterConfig.baudRate = frequency;

	masterConfig.pcsToSckDelayInNanoSec        = 1000000000U / (masterConfig.baudRate * 2U);
	masterConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / (masterConfig.baudRate * 2U);
	masterConfig.betweenTransferDelayInNanoSec = 1000000000U / (masterConfig.baudRate * 2U);

	LPSPI_Deinit( EXAMPLE_LPSPI_MASTER_BASEADDR );
	LPSPI_MasterInit( EXAMPLE_LPSPI_MASTER_BASEADDR, &masterConfig, LPSPI_MASTER_CLK_FREQ );
}

void SPI::mode( uint8_t mode )
{
	masterConfig.cpol	= (lpspi_clock_polarity_t)((mode >> 1) & 0x1);
	masterConfig.cpha	= (lpspi_clock_phase_t   )((mode >> 0) & 0x1);

	LPSPI_Deinit( EXAMPLE_LPSPI_MASTER_BASEADDR );
	LPSPI_MasterInit( EXAMPLE_LPSPI_MASTER_BASEADDR, &masterConfig, LPSPI_MASTER_CLK_FREQ );	
}

status_t SPI::write( uint8_t *wp, uint8_t *rp, int length )
{
	lpspi_transfer_t	masterXfer;

	masterXfer.txData		= wp;
	masterXfer.rxData		= rp;
	masterXfer.dataSize		= length;
	masterXfer.configFlags	= EXAMPLE_LPSPI_MASTER_PCS_FOR_TRANSFER | kLPSPI_MasterPcsContinuous | kLPSPI_MasterByteSwap;

	return LPSPI_MasterTransferBlocking( EXAMPLE_LPSPI_MASTER_BASEADDR, &masterXfer );
}
