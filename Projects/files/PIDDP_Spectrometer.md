## People

Robert Abiad, Luis Esteban Hernández, Robert Jarnot, Eric Korpela, Juan
Antonio Lopez Martin, Ryan Monroe, Borivoje Nikolic, Rick Raffanti,
Brian Richards, Rachel Hochman, Paul Stek, Mark Wagner, Dan Werthimer

## Overview

**SPLASH**    **S**ingle-chip **P**lanetary **L**ow-power **A**SIC
**S**pectrometer with **H**igh-resolution

We are developing a low power, high resolution, digital spectrometer
ASIC with on-chip ADC. The ASIC will provide a compact, low power, and
radiation tolerant digital polyphase filterbank for analyzing microwave
thermal emission following the first downconversion in a microwave
radiometer. This spectrometer is intended for use in future microwave
sounders observing the atmospheres of planets such as Mars or Venus,
moons of Jupiter and Saturn, and may also find applications in
terrestrial CubeSat radiometers. The mixed signal ASIC spectrometer will
have significant improvements in terms of mass, power, volume, and
sensitivity to environmental conditions compared to other technologies
such as Chirp-transform, Acousto-optical and digital autocorrelator
spectrometers. The largely digital nature of the implementation will
also reduce calibration requirements and increase stability compared to
alternative approaches. SPLASH will integrate ADC, digital spectroscopy
and spectral integration functions onto a single mixed-signal ASIC. Our
novel approach to this ASIC uses an on chip ultra-low power 3 GS/s ADC
(for a bandwidth of 1.5 GHz) utilizing capacitive successive
approximation and self calibration. The ADC is followed by a 8192
channel digital 4 tap polyphase filter bank to achieve excellent
channel-to-channel isolation. The proposed 2.7 by 2.7 mm ASIC will be
fabricated on a naturally radiation tolerant 65 nm CMOS process. The
SPLASH ASIC will consume \(<\)1 W, and deliver a throughput of 300
billion operations per second. The design is based on a digital
architecture described in Simulink that has been field-tested on FPGA
platforms for radio astronomy applications. The architecture maximizes
the utilization of operators to nearly 100%. A test structure has been
added to the design to support the detection of soft errors, since
space-borne applications expose the circuit to high-energy particles. An
in-house automated design flow will be used to map the same Simulink
description to the ASIC, preserving cycle-accurate and bit-accurate
behavior.

On successful completion of this project we anticipate proposal of a low
power ASIC spectrometer with considerably greater bandwidth (10 GHz) and
higher resolution (32768 channels or more) intended for a broad range of
applications.

## Specifications

Key parameters/specifications of the SPLASH spectrometer include:

  - Single chip, low power, 1.5 GHz bandwidth, 8192 channel, digital
    polyphase spectrometer
  - 375 MHz ASIC clock rate
      - Clock provided from an external source. If clock dithering
        capability is provided on chip for the digital portion of the
        ASIC, there shall be the capability to disable it
  - 8 bit, self calibrating, embedded ADC
      - The ADC does not provide an indication of over/under range input
        signals
          - An over/under-range input signal results in an ADC output of
            all 0's or all 1's
          - Input signals to the ADC must not exceed the full scale
            input range to the extent that the protection diodes are
            biased with excessive current.
          - There is no additional recovery time from input overload
            signals
      - An ADC data capture mode shall be implemented which replaces
        spectral data with ADC data
      - Background self calibration takes place only over the range of
        the input signal
      - Background calibration should be disabled while science data is
        being acquired
      - The time for which background calibration can be disabled for
        extended periods (months) if ADC temperature is stable
  - 65 nm bulk CMOS, naturally rad-hard. Design steps will be taken to
    avoid latch-up. The ST 65 nm bulk CMOS process has been tested to
    100 kRad with negligible change in chip performance. The goal is to
    implement a chip hard to at least 300 kRad to accommodate the
    radiation environment of a proposed Jupiter mission which targets
    atmospheric measurements of several Jovian moons
      - Impact of SEUs (bit flips) will be self-clearing to the extent
        possible (as in the previous digital-only spectrometer ASIC)
      - A test vector generator (TVG) shall be included to allow
        periodic verification of spectrometer functionality to detect
        any non self-clearing SEU events
  - A reset pin shall be available to return the ASIC to a known state
      - Do we need to elaborate further on the power-up state? For
        example, should we *require* an external reset to the chip after
        power up?
  - 4 tap PFB with 3 dB scalloping (we should provide the name of the
    windowing function if it has one)
  - External sync input to trigger spectral measurements
      - The PFB and FFT blocks shall run continuously, with spectral
        measurements always being in units of complete FFT cycles
      - A positive edge shall trigger the start of an integration (and
        be ignored if an integration is already in progress)
      - A continuous high level at the sync input shall result in
        back-to-back data integrations
      - Accumulated data shall be double buffered to allow concurrent
        data acquisition and readout
      - The number of FFT cycles in a data integration shall be
        programmable, ranging from a single integration up to at least
        \(2^{16}\) cycles (\(2^{20}\) cycles preferred)
      - For integration times longer than a single FFT cycle it is
        acceptable to have a granularity larger than individual FFT
        cycles. For example, a granularity of 64 FFT cycles provides
        integration time increments of \(\sim\)0.35 ms, allowing a 16
        bit integration time request to provide integration times up 20
        s.
      - Note that since data integrations are in units of FFT cycles, if
        several SPLASH spectrometers are used in parallel (with the same
        sync input signal), individual spectrometer data integrations
        may be time shifted relative to one another by up to 5.5 μs.
        This is not an issue for the intended applications for this
        spectrometer
  - ASIC control/configuration shall be by a combination of external
    pins (e.g. RESET and sync) and internal registers (e.g. integration
    time)
      - Programmable internal registers shall be hardened against SEUs.
        This can be performed by using triple modular redundancy and
        voting logic, or by implementing registers that are rad-hard by
        design. If TMR is used, it is important to verify that an SEU
        did not corrupt the register load operation. This can be
        achieved by either:
          - implementing a register readback capability
          - requiring that three input registers be individually loaded
            with the same data, with the output register being loaded
            upon loading the final input register conditional upon
            successful comparison/voting of the input register contents.
            A comparison/voting anomaly shall be reported by an output
            pin. A common output pin may be used to report errors in
            several register sets, in which case a mechanism shall be
            implemented to allow determination of which register set
            needs to be reloaded. A suitable reporting mechanism is to
            include a status word in the spectral data frame output by
            the spectrometer
  - The serial command interface shall consist of a data, clock and
    enable line, similar to the previous ASIC spectrometer chip.
  - Serial data readout of spectral (or ADC) data shall be in nibble or
    byte serial format, with the ASIC providing clock and enable signals
      - Data (clock) rate of this readout shall not exceed 50 MHz
          - Note that the readout format will place a restriction on the
            shortest data integration time for which continuous data
            readouts are possible without inter-integration time gaps.
            For example, a byte wide 50 MHz readout will take
            approximately 1.3 ms (assuming 64 bit data)
          - If an integration time shorter than the frame readout time
            is selected, the sync logic shall prevent the next data
            integration from starting until a new data buffer is
            available. This preserves the integration time selected by
            the user, but may result in gaps between data integrations
  - Coefficient and data word widths are TBD
      - The block diagram below should be updated to reflect the current
        design, and annotated with word widths. It may be useful to
        include information on rounding methods where data widths are
        reduced (e.g. if not all data bits from the squared FFT output
        are fed to the vector accumulator block). It may be worth
        including a link to a top level Simulink diagram of the
        spectrometer too

## Performance

The parameters/specifications in the previous section are 'by design'.
In addition to these requirements, the following performance
characteristics shall be measured:

  - Channel shapes shall be measured by CW sweeps, and shall correspond
    to theoretical channel shapes. If the theoretical channel shapes are
    computed using floating point arithmetic, then allowance for
    differences between measured and calculated channel shapes shall be
    provided
  - Dynamic range
      - The definition of dynamic range relates to the ability of the
        measurement system to resolve a small (0.1 K equivalent
        brightness), narrow (several channels wide) signal on top of a
        large noise background (1000 K equivalent)
      - This test was performed on the Mars Spectrometer ASIC
        <need a link to the test report>
  - Linearity
      - All digital spectrometer systems exhibit non-linearity due to
        finite ADC resolution and integer DSP arithmetic. For this
        spectrometer we need to verify that measured linearity
        corresponds to theoretical predictions. This topic needs to be
        expanded upon, and should probably make mention of the Van Vleck
        correction, since this shows that non-linearity distorts the
        measured spectrum, as well as introducing errors in the
        amplitude domain
  - Total Power Allan Variance
      - The Total Power Allan Variance breakpoint time shall be
        measured, with a goal of 500 s or longer
  - Spectral Allan Variance
      - The Spectral Allan Variance breakpoint time shall be measured,
        with a goal of 5000 s or longer
  - Channel Noise Bandwidth shall be measured using a noise source as
    the input signal, and be in accordance with theoretical predictions
  - The impact of temperature and supply voltage changes on ADC
    performance shall be measured in order to determine when an ADC
    background calibration cycle is needed in an operational environment
      - We need to address the impact of radiation exposure on
        calibration intervals too

The following performance characteristics shall be measured/verified and
documented:

  - Operating voltage range
  - Operating frequency range
  - Bandpass flatness when the input is swept with a fixed amplitude
    tone
  - Functionality over the full temperature range (-55°C to +125°C, TBR)
  - Power consumption over the operating temperature and voltage range
  - Timing margins on the serial command interface
  - Probably lots of other things

## Reliability

  - The ASIC shall not exhibit destructive latch-up when exposed to TBD
    heavy ion exposure
      - Need to come up with some realistic requirements in this area
      - If non-destructive latch-up is a possibility, we need to discuss
        how this can be detected (power supply current?), and how to
        recover (power cycling?)
  - JPL Division 5X shall provide guidance for:
      - Radiation testing (SEU)
      - Latch-up testing (SEL)
      - Lifetime testing (how many devices are needed for this?)
      - Destructive testing (how many devices are needed for this?)
      - Design rules
      - Design for test/visibility into internal operation of the ASIC
      - Packaging fir a flight environment
      - Manufacturing flow for flight certified devices
      - Other necessary steps for qualification for flight use of these
        devices
      - Any other reliability and qualification related issues
      - We need to be conscious of the need to prevent reliability
        related costs from getting out of hand

<!-- end list -->

  - May need to add some words on design for test, and scan chain used
    to force/monitor internal nodes

## Data Sheet

  - A data sheet shall be created for the SPLASH ASIC
      - This should start as a skeleton, with information added as it
        becomes available
  - Necessary data include (but not limited to):
      - Absolute maximum ratings
      - Radiation hardness (to the extend possible)
      - Power supply voltages, ranges and currents
      - Operating and survival temperature limits
      - Package/pin description
      - Description of all user modes of the ASIC
      - Description of all data packets returned by the ASIC
      - Description of all commands recognized by the ASIC
      - All of the other information expected in a data sheet for this
        type of device (setup and hold times, waveform diagrams for
        serial commands and data, and so on)
      - A description of the ADC auto-calibration, and its implications.
        For example:
          - How long does it take for the auto-calibration to take
            effect when there is a significant increase in the input
            signal power to the spectrometer?
          - Is it advisable to feed the input of the ASIC with a
            full-scale input signal periodically, if so, how frequently,
            and what is the impact on auto-calibration of a signal which
            over-ranges the input?

<!-- end list -->

  - A test report which describes the tests performed on the ASIC, and
    the results, is highly desirable

## Board Level Details

  - The prototype board-level spectrometer shall implement:
      - A clock (oscillator) for the ASIC clock input
      - Protection of the ADC signal input pins against damaging
        overload (excessive protection diode current)
      - A calibration signal generator use with the ADC auto-calibration
        mode. This will require a mechanism for switching between the
        science data and calibration signals
      - Other items to be determined after consultation with potential
        customers

## The Team

The Berkeley team (which should be listed somewhere on this page,
together with responsibilities) are responsible for the design,
implementation, and testing of the ASIC. The JPL team (which should also
be listed) will be collaborating on refinement of specifications, the
design and implementation of an FPGA prototype (used to verify the DSP
design), and on evaluating the MatLab model and FPGA prototype to verify
that the intended performance goals are met.

## Block Diagram

This diagram needs to be replaced with an updated one.
![Asic\_spectrometer\_bloack\_diagram.png](Asic_spectrometer_bloack_diagram.png
"Asic_spectrometer_bloack_diagram.png")

## Testing

[radiation test report which includes the ST 65 nm bulk CMOS
process](https://casper.berkeley.edu/wiki/images/a/af/1234799491626110_ESA_QCA_days_2009_ST_2007_contract_Roche.pdf)

[Polyphase ﬁlter bank quantization error
analysis](https://casper.berkeley.edu/wiki/images/1/1c/Polyphasequant.pdf)
September 2003 (J. Stemerdink)
