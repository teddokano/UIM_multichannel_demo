/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"r01lib.h"
#include	"afe/NAFE13388_UIM.h"
#include	"utils.h"

SPI				spi( D11, D12, D13, D10 );	//	MOSI, MISO, SCLK, CS
NAFE13388_UIM	afe( spi );

constexpr auto	n_lc	= 8;

long			dp[  n_lc ];
double			dvp[ n_lc ];
volatile bool	conversion_done	= false;

void drdy_callback( void )
{
	afe.read( dp );

	for ( auto i = 0; i < n_lc; i++ )
		dvp[ i ]	= afe.raw2v( i, dp[ i ] );

	conversion_done	= true;
}

int main( void )
{
	printf( "***** Hello, NAFE13388 UIM board! *****\r\n" );

	spi.frequency( 1'000'000 );
	spi.mode( 1 );

	afe.begin();
	afe.blink_leds();

	uint64_t	sn	= afe.serial_number();

	printf( "part number   = %04lX (revision: %01X)\r\n", afe.part_number(), afe.revision_number() );
	printf( "serial number = %06lX%06lX\r\n", (uint32_t)(sn >> 24), (uint32_t)sn & 0xFFFFFF );	//	to use NewlibNano
	printf( "die temperature = %f℃\r\n", afe.temperature() );

	RegVct	registers	= { PN2, PN1, PN0, SERIAL1, SERIAL0, DIE_TEMP, SYS_CONFIG0, SYS_STATUS0 };
	reg_dump( registers );

	constexpr uint16_t	cc0	= 0x0010;
	constexpr uint16_t	cc1	= 0x007C;
	constexpr uint16_t	cc2	= 0x4C00;
	constexpr uint16_t	cc3	= 0x0000;

	for (  auto i = 0; i < n_lc / 2; i++ )
	{
		afe.open_logical_channel(  i * 2 + 0, cc0 | (i + 1) << 12 | 7       << 8, cc1, cc2, cc3 );
		afe.open_logical_channel(  i * 2 + 1, cc0 | 7       << 12 | (i + 1) << 8, cc1, cc2, cc3 );
	}

	printf( "\r\nenabled logical channel(s) %2d\r\n", afe.enabled_logical_channels() );
	logical_ch_config_view();

	afe.set_DRDY_callback( drdy_callback );	//	set callback function for when DRDY detected
	afe.DRDY_by_sequencer_done( true );		//	generate DRDY at all logical channel conversions are done

	afe.start_continuous_conversion();

	while ( true )
	{
		if ( conversion_done )
		{
			conversion_done	= false;

			for ( auto i = 0; i < n_lc; i++ )
			{
//				printf( "  %8ld,", dp[ i ] );
				printf( "  %10.8lf,", dvp[ i ] );
			}

			printf( "  %10.8lf,",afe.raw2v( 0, dp[ 0 ] ) );

			printf( "\r\n" );
		}
	}
}
