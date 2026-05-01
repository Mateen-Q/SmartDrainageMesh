# **Smart Drainage Mesh**
### **Reactive WSN Approach to Urban Flood Monitoring using TEEN Protocol**

## **Overview**
Urban flood monitoring systems often face a critical trade-off between real-time responsiveness and energy longevity. This project implements a **Reactive Wireless Sensor Network (WSN)** designed for automated drainage infrastructure. Unlike traditional proactive systems that waste power on redundant "all-clear" data, this mesh network remains in a low-power state until environmental thresholds are breached.

The system is built on **Contiki-NG**, utilizing the **NullNet** networking stack for lean, high-efficiency communication[cite: 4]. Validation was performed using the **Cooja Simulator** with a 10-node sensor grid and a central aggregating gateway[cite: 1].

---

## **Key Features**
*   **TEEN Protocol Implementation:** Utilizes a dual-threshold reactive logic to minimize radio duty cycles[cite: 2].
*   **Spatial Data Aggregation:** The Sink node processes incoming alerts to isolate and report only the maximum detected flood levels[cite: 3].
*   **Resilient Mesh Topology:** Modeled using the Unit Disk Graph Medium (UDGM) to simulate realistic urban radio signal loss[cite: 1].
*   **Modular C Firmware:** Clean separation of concerns between sensing logic and network communication[cite: 2, 3].

---

## **Technical Architecture**

### **1. Firmware Logic (TEEN Protocol)**
The sensor nodes execute a "Decision-Before-Transmission" cycle to preserve battery life:
*   **Hard Threshold ($H_T = 30\text{cm}$):** Nodes remain silent until the water level exceeds this critical limit[cite: 2].
*   **Soft Threshold ($S_T = 2\text{cm}$):** Once an alert state is active, new data is only transmitted if the water level shifts by $\ge 2\text{cm}$[cite: 2].

$$|L_{current} - L_{last\_sent}| \ge S_T$$

### **2. Data Aggregation**
The Sink node acts as the intelligence hub. To prevent "Data Implosion" during a flood event, it performs a comparison on all incoming packets:
*   **Aggregation Formula:** $V_{agg} = \max(V_1, V_2, \dots, V_n)$[cite: 3].
*   Only "New Aggregated Max" events are logged for external emergency triggers, reducing redundant cloud traffic[cite: 3].



---

## **Repository Structure**
*   **/src**: Contains the Contiki-NG source code (`flood-sensor.c`, `sink-node.c`) and the project `Makefile`[cite: 2, 3, 4].
*   **/simulation**: The `Flood_Detection.csc` file for reproducing the 11-mote environment in Cooja[cite: 1].
*   **/docs**: Technical documentation including flowcharts and hardware schematics.
*   **/images**: Screenshots of simulation results and duty cycle analysis.

---

## **How to Run**

### **Prerequisites**
*   Docker installed on your machine.
*   The Contiki-NG Docker image (`contiker/contiki-ng`).

### **Simulation Steps**
1.  **Clone the Repo:**
    ```bash
    git clone https://github.com/YOUR_USERNAME/Smart-Drainage-Mesh.git
    cd Smart-Drainage-Mesh/src
    ```
2.  **Compile Firmware:**
    ```bash
    # From inside the Contiki-NG Docker container
    make TARGET=cooja
    ```
3.  **Launch Cooja:**
    Open the `simulation/Flood_Detection.csc` file within the Cooja GUI[cite: 1].
4.  **Analyze Logs:**
    Observe the **Mote Output** to see the TEEN logic in action and the Sink node’s aggregation logs[cite: 1, 3].

---

## **Hardware Implementation (Conceptual)**
While validated in simulation, the firmware is designed for deployment on low-power hardware:
*   **Microcontroller:** ESP32 (Support for Deep Sleep).
*   **Sensor:** HC-SR04 Ultrasonic Transducer.
*   **Communication:** SX1276 LoRa Module (for long-range mesh connectivity).
*   **Power:** 3.7V Li-Po with Solar Harvesting.

---

## **License**
This project is licensed under the MIT License - see the LICENSE file for details.

---
