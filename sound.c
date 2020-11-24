#include "myLib.h"
#include "sound.h"

void setupSounds()
{
    REG_SOUNDCNT_X = SND_ENABLED;

    REG_SOUNDCNT_H = SND_OUTPUT_RATIO_100 |
                     DSA_OUTPUT_RATIO_100 |
                     DSA_OUTPUT_TO_BOTH |
                     DSA_TIMER0 |
                     DSA_FIFO_RESET |
                     DSB_OUTPUT_RATIO_100 |
                     DSB_OUTPUT_TO_BOTH |
                     DSB_TIMER1 |
                     DSB_FIFO_RESET;

    REG_SOUNDCNT_L = 0;
}

void playSoundA( const signed char* sound, int length, int loops) {
        dma[1].cnt = 0;

        int ticks = PROCESSOR_CYCLES_PER_SECOND / SOUND_FREQ;

        DMANow(1, sound, REG_FIFO_A, DMA_DESTINATION_FIXED | DMA_AT_REFRESH | DMA_REPEAT | DMA_32);

        REG_TM0CNT = 0;

        REG_TM0D = -ticks;
        REG_TM0CNT = TIMER_ON;

        // Assign all of soundA’s appropriate struct values
        soundA.data = sound;
        soundA.length = length;
        soundA.isPlaying = 1;
        soundA.loops = loops;
        soundA.frequency = SOUND_FREQ;
        soundA.duration = ((VBLANK_FREQ*length)/SOUND_FREQ);  
        soundA.vBlankCount = 0;
}


void playSoundB( const signed char* sound, int length, int loops) {

        dma[2].cnt = 0;

        int ticks = PROCESSOR_CYCLES_PER_SECOND / SOUND_FREQ;

        DMANow(2, sound, REG_FIFO_B, DMA_DESTINATION_FIXED | DMA_AT_REFRESH | DMA_REPEAT | DMA_32);

        REG_TM1CNT = 0;

        REG_TM1D = -ticks;
        REG_TM1CNT = TIMER_ON;

         // Assign all of soundB’s appropriate struct values
        soundB.data = sound;
        soundB.length = length;
        soundB.isPlaying = 1;
        soundB.loops = loops;
        soundB.frequency = SOUND_FREQ;
        soundB.duration = ((VBLANK_FREQ*length)/SOUND_FREQ);  
        soundB.vBlankCount = 0;
}

void setupInterrupts()
{
    REG_IME = 0;

    // Set up the interrupt handler
    REG_INTERRUPT = interruptHandler;

    REG_IE |= INT_VBLANK;
    REG_DISPSTAT |= INT_VBLANK_ENABLE;
    REG_IME = 1;
}

void interruptHandler() {
	REG_IME = 0;

	if(REG_IF & INT_VBLANK) {
        if (soundA.isPlaying) {

            // Handle soundA playing in the interruptHandler function
            soundA.vBlankCount = soundA.vBlankCount + 1;
            if (soundA.vBlankCount > soundA.duration) {
                if (soundA.loops) {
                    playSoundA(soundA.data, soundA.length, soundA.loops);
                } else {
                    soundA.isPlaying = 0;
                    dma[1].cnt = 0;
                    REG_TM0CNT = TIMER_OFF;
                }
            }
        }

        if (soundB.isPlaying) {

            // Handle soundB playing in the interruptHandler function
            soundB.vBlankCount = soundB.vBlankCount + 1;
            if (soundB.vBlankCount > soundB.duration) {
                if (soundB.loops) {
                    playSoundB(soundB.data, soundB.length, soundB.loops);
                } else {
                    soundB.isPlaying = 0;
                    dma[2].cnt = 0;
                    REG_TM1CNT = TIMER_OFF;
                }
            }
		}


		REG_IF = INT_VBLANK;
	}

	REG_IME = 1;
}

void pauseSoundA() {
	soundA.isPlaying = 0; // sound A playing false
	REG_TM0CNT = TIMER_OFF; // stop timer
}

void pauseSoundB() {
	soundB.isPlaying = 0; // sound B playing false
	REG_TM1CNT = TIMER_OFF; // stop timer
}

void unpauseSoundA() {
	soundA.isPlaying = 1;
	REG_TM0CNT = TIMER_ON;
}

void unpauseSoundB() {
	soundB.isPlaying = 1;
	REG_TM1CNT = TIMER_ON;	
}

void stopSoundA() {
	dma[1].cnt = 0;
	soundA.isPlaying = 0;
	REG_TM0CNT = TIMER_OFF;
}

void stopSoundB() {
	dma[2].cnt = 0;
	soundB.isPlaying = 0;
	REG_TM1CNT = TIMER_OFF;	
}