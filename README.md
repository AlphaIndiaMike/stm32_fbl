# STM32F746G Bootloader

## Overview

A custom bootloader for the STM32F746G microcontroller.

## Key Features

- Flexible application start addresses

## Suggested Memory Layout

- BL memory start: 0x08000000
- Application memory start: 0x08008000

## Troubleshooting

- Verify 32 KB-aligned start addresses for applications (STM32F7)
- Verify 2 KB-aligned start addresses for applications (STM32G4, STM32L4)
- Check flash memory contents with a debug probe
- Review flash protection settings and boot configurations
