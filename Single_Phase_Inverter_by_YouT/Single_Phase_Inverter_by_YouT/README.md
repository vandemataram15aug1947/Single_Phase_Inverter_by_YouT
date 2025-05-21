# 🌀 Single-Phase Inverter Using SPWM (Sinusoidal Pulse Width Modulation)

## 📘 Overview

This embedded systems project implements a **single-phase inverter** using **Sinusoidal Pulse Width Modulation (SPWM)** on the **TI TMS320F28379D** microcontroller. The design generates two sine-modulated PWM waveforms (180° out of phase), suitable for controlling a full-bridge or half-bridge inverter to synthesize a 50/60 Hz AC voltage waveform from a DC supply.

This implementation is targeted toward students, researchers, and engineers working in the field of **power electronics**, especially in applications like:

- Solar inverters
- UPS systems
- Grid-connected inverters
- Induction heating systems
- Single-phase AC drive systems

---

## 🎯 Project Goals

- ✅ Generate high-resolution sinusoidal PWM signals for inverter switching.
- ✅ Understand CPU Timer interrupt-based waveform synthesis.
- ✅ Use precomputed sine tables to simplify computation.
- ✅ Output sinusoidal PWM signals from two PWM channels (ePWM7 and ePWM8).
- ✅ Design modular and scalable code architecture for further expansion.

---

## 🧠 Theory and Background

### ➕ SPWM Fundamentals

SPWM is a technique where a sinusoidal reference is compared to a high-frequency triangular carrier. The resulting PWM waveform has varying duty cycles that match the reference sinusoid. The inverter's output filtered with an LC or LCL filter results in a sinusoidal voltage waveform.

### 📐 Frequency and Resolution

- A sine table with 125 samples covers one full cycle (0°–360°).
- The switching frequency is indirectly defined by the update rate of the CMPA register in each timer interrupt.
- The sine table ensures the waveform is smooth and consistent without computing sine values in real-time.

---

## ⚙️ System Architecture

### 📁 Modular File Structure

```plaintext
Single_Phase_Inverter_SPWM/
│
├── Peripheral_Setup.h        # Header file for function declarations
├── Peripheral_Setup.c        # Function definitions for GPIO and PWM configuration
├── Single_Phase_Inverter_by_YouT.c  # Main application with timer ISR and sine generation
├── README.md                 # Full documentation
