# Heart Rate Monitor

This project involves the development of a heart rate monitor using the PIC16F628A microcontroller and a piezoelectric sensor. It is a semester project that integrates the contents of the classes "Microcontroladores e Sistemas Controlados" (Microcontrollers and Controlled Systems) and "Instrumentação" (Instrumentation). During the semester, these classes provided knowledge about programming the PIC16F628A and working with various sensors. Applying this knowledge, a device was created to process the sensor signals and display the heart rate on three 7-segment displays, consolidating the learned theory and addressing practical challenges in biomedical monitoring.

## Summary
- [Material e Methods](#Material and Methods)


# Material and Methods

The first step to start the project was to decide which sensor would be responsible for measuring the heartbeats. After researching and discussing with Professor Andressa Martins, it was concluded that a piezoelectric sensor would be a suitable solution. The piezoelectric sensor generates an electric charge proportional to the mechanical stress applied to it; thus, when placed over an arterial vein, each heartbeat causes a pulse in the vein that presses the sensor, generating a detectable pulse.

With the heartbeat sensing sensor defined, its analysis began. Initially, the signal from a 0.002 m diameter piezoelectric sensor was analyzed. However, this size caused difficulties in soldering and handling, as well as generating a lower and noisier voltage, making it harder to read on the oscilloscope (Figure 2). For these reasons, it was decided to replace the sensor with a 0.003 m diameter piezoelectric sensor (Figure 1). This change not only facilitated the soldering and handling of the component but also resulted in an improvement in signal reading, both in terms of noise and generated voltage (Figure 3).
