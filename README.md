# PES-Assignment-7
# Getting in Tune

## Objective of the Assignment <br/>
The objective of this assignment is to generate four notes (frequencies) namely - 440Hz, 587Hz, 659Hz and 880Hz for 1sec period.</br>
After reaching the end frequency, it should restart from the beginning. The requirement of this assignment is to use the Digital to Analog Converter</br>
(DAC) to generate the frequencies using the Direct Machine Access (DMA). And then using the Analog to Digital Converter to read teh frequencies and analyze them.

## Implementation
1) Tone_To_Samples() function is impemented to compute the number of samples in certain cycle (depends of the input frequency).</br>
2) These samples are stored in a buffer which then passes to the DAC using DMA to generate the waveform using those number of samples.</br>
3) Once this waveform is generated, the iternation will run for several times until the systick counter reaches 100 (1 count = 10 msec).</br>
4) After reaching to that value, the change in frequency occurs i.e the frequency gets changed from 440Hz to 587Hz.</br>
5) Once the waveform is generated, the ADC reads the samples from the generated waveform and converts it into digital value.</br>
6) This digial value is analyzed to get to know the maximum and minimum amplitude of the generated sine waveform.</br>
7) To play each note for 1sec, systick() timer has been used in order to accompish this task.

4) This process remains same for all the four frequencies.</br>

## Extra Credit
1) The waveforms were made to display on the oscilloscope in order to check if the frequencies and correctly displayed and for 1sec period i.e. each notes should be </br>
played for only 1sec. Pictures are uploaded on the GitHub.










