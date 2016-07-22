# wall_tracer
Wall tracer example with ATMEGA8


## Pin configuration 
  ![board_image](http://rc423.com/rc423/walltr_images.png)


## Outputs of my code
| PD6  | PD5  | PD4  | PD3  | PD2  | PD1 | PD0 |
|------|------|------|------|------|-----|-----|
| AIN1 | AIN2 | BIN1 | BIN2 | STBY | X   | X   |
| H    |L    | L    | H    | H    | X   | X   |

## Explanation of input/output value
  <table class="tg">
  <tr>
    <th class="tg-yw4l" colspan="4">Input</th>
    <th class="tg-yw4l" colspan="3">Output</th>
  </tr>
  <tr>
    <td class="tg-yw4l">IN1</td>
    <td class="tg-yw4l">IN2</td>
    <td class="tg-yw4l">PWM</td>
    <td class="tg-yw4l">STBY</td>
    <td class="tg-yw4l">OUT1</td>
    <td class="tg-yw4l">OUT2</td>
    <td class="tg-yw4l">Mode</td>
  </tr>
  <tr>
    <td class="tg-yw4l">H</td>
    <td class="tg-yw4l">H</td>
    <td class="tg-yw4l">H/L</td>
    <td class="tg-yw4l">H</td>
    <td class="tg-yw4l">L</td>
    <td class="tg-yw4l">L</td>
    <td class="tg-yw4l">Short brake</td>
  </tr>
  <tr>
    <td class="tg-yw4l" rowspan="2">L</td>
    <td class="tg-yw4l" rowspan="2">H</td>
    <td class="tg-yw4l">H</td>
    <td class="tg-yw4l">H</td>
    <td class="tg-yw4l">L</td>
    <td class="tg-yw4l">H</td>
    <td class="tg-yw4l">CCW</td>
  </tr>
  <tr>
    <td class="tg-yw4l">L</td>
    <td class="tg-yw4l">H</td>
    <td class="tg-yw4l">L</td>
    <td class="tg-yw4l">L</td>
    <td class="tg-yw4l">Short brake</td>
  </tr>
  <tr>
    <td class="tg-yw4l" rowspan="2">H</td>
    <td class="tg-yw4l" rowspan="2">L</td>
    <td class="tg-yw4l">H</td>
    <td class="tg-yw4l">H</td>
    <td class="tg-yw4l">H</td>
    <td class="tg-yw4l">L</td>
    <td class="tg-yw4l">CW</td>
  </tr>
  <tr>
    <td class="tg-yw4l">L</td>
    <td class="tg-yw4l">H</td>
    <td class="tg-yw4l">L</td>
    <td class="tg-yw4l">L</td>
    <td class="tg-yw4l">Short brake</td>
  </tr>
  <tr>
    <td class="tg-yw4l">L</td>
    <td class="tg-yw4l">L</td>
    <td class="tg-yw4l">H</td>
    <td class="tg-yw4l">H</td>
    <td class="tg-yw4l" colspan="2">OFF<br>(High impedance)</td>
    <td class="tg-yw4l">Stop</td>
  </tr>
  <tr>
    <td class="tg-yw4l">H/L</td>
    <td class="tg-yw4l">H/L</td>
    <td class="tg-yw4l">H/L</td>
    <td class="tg-yw4l">L</td>
    <td class="tg-yw4l" colspan="2">OFF<br>(High impedance)</td>
    <td class="tg-yw4l">Stanby</td>
  </tr>
</table>



---
Work done by POWER-ON, POSTECH
