# Cost Analysis: LoRaWAN vs. Mesh Network (ZAR)

## 1. Introduction

### LoRaWAN (Standard)
LoRaWAN requires a star-topology where all sensors speak directly to a Gateway. This usually requires expensive, high-performance gateways but allows for cheap, standardized sensor modules.
*   **CAPEX**: High (Gateways) / Low (Nodes)
*   **OPEX**: Moderate (Recurring Network Server fees)

### Mesh Network (Proprietary/Dual-Band)
Mesh allows nodes to relay data to each other, forming a dynamic network that funnels to a simple, low-cost gateway.
*   **CAPEX**: Low (Gateways) / High (Nodes)
*   **OPEX**: Low (Self-managed, no external LNS fees assumed)

---

## 2. Assumptions & Scope

**Currency Exchange**: $1 = R16.16  |  €1 = R19.16

### Exclusions
*   Backhaul Connectivity (SIM/Ethernet cost).
*   Sensor Manufacturing Base Cost (Housing/Battery/PCB).

### Inclusions
*   **Hardware**: Radio Modules & Gateways.
*   **Software**: LoRaWAN Network Server (LNS) is now included as a **monthly recurring cost**.

---

## 3. Cost Parameters

| Component | Standard LoRaWAN | Mesh (Dual-Band) | Notes |
| :--- | :--- | :--- | :--- |
| **Radio Module (CAPEX)** | **R120.00** | **R422.00 (€22)** | Mesh module is ~R300 more expensive per unit. |
| **Gateway (CAPEX)** | **R2,297.00** | **R950.00** | LoRaWAN Gateway is ~R1,350 more expensive. |
| **LNS Fee (OPEX)** | **R3.7167/ month** | **R0.00** | Based on **R 3716,80** ($230)/1000 devices/month. Mesh is zero-rated for local routing. |

---

## 4. Total Cost of Ownership (TCO) & Projections

Since LoRaWAN has an ongoing cost, we must compare Total Cost over time ($M$ months).

### Formula
$$ \text{Cost}(M) = (\text{Nodes} \times \text{ModuleCost}) + (\text{Gateways} \times \text{GWCost}) + (\text{Nodes} \times \text{MonthlyFee} \times M) $$

### Scenario A: Large Scale (1000 Sensors, 5 Gateways)
*Context: A large commercial deployment.*
*   **LoRaWAN CAPEX**: (R2,297.00 * 5) + (R120.00 * 1000) = R11,485.00 + R120,000.00 = **R 131,485.00**
*   **Mesh CAPEX**: (R950.00 * 5) + (R422.00 * 1000) = R4,750.00 + R422,000.00 = **R 426,750.00**
*   **Initial Diff**: LoRaWAN is **R295,265 cheaper** upfront.
*   **LoRaWAN OPEX**: 1000 * R3.76188 = **R3,716.80 / month**
*   **Break Even Time**: R295,265.00 / R3,716.80 ≈ **79 months**
**Result**: LoRaWAN is cheaper for the first **6.6 Years**. After 6.7 years, the cumulative monthly fees exceed the one-time savings on modules.

### Scenario B: Medium Scale (100 Sensors, 2 Gateway)
*Context: A typical smart-farm.*
*   **LoRaWAN CAPEX**: (R2,297.00 * 2) + (100 * R120.00) = R4,594.00 + R12,000.00 = **R 16,594.00**
*   **Mesh CAPEX**: (R950.00 * 2) + (100 * R422.00) = R1,900.00 + R42,200.00 = **R 44,100.00**
*   **Initial Diff**: LoRaWAN is **R27,506.00 cheaper**.
*   **LoRaWAN OPEX**: R3.7168 * 100 = **R 371.68 / month**
*   **Break Even Time**: R27,506.00 / R 371.68 ≈ **74 months**
**Result**: Consistent with the large sale; LoRaWAN wins for any project shorter than **~6.16 years**.

### Scenario C: Small & Complex (10 Sensors, 5 Gateways)
*Context: A confusing layout (tunnels/basements/hills) requiring many gateways for few devices.*
*   **LoRaWAN CAPEX**: (R2,276.00 * 5) + (R 120.00 * 10) = R 11,380.00 + R 1,200.00 = **R 12,580.00**
*   **Mesh CAPEX**: (R 950.00 * 5) + (R 422.00 * 10) = R 4,750.00 + R 4,220.00 = **R 8,970.00**
*   **Initial Diff**: Mesh is **R3,610.00 cheaper** upfront.
*   **LoRaWAN OPEX**: **R45.30 / month**
**Result**: Mesh starts cheaper and **stays cheaper forever**. LoRaWAN never catches up because it has higher CAPEX *and* higher OPEX in this scenario.

### 4.4 Exact Break-Even Point (5 Gateways, 60 Months)
To find the exact number of nodes ($N$) where LoRaWAN and Mesh costs are equal over a 5-year (60 month) period with 5 Gateways:

**The Variables:**
*   **Gateway Cost Diff**: $5 \times (R2,297 - R950) = R6,735$ (Infrastructure debt of LoRaWAN)
*   **Module Cost Diff**: $R422 - R120 = R302$ (Upfront unit saving of LoRaWAN)
*   **Operational Cost (60 mo)**: $R3.7167 \times 60 = R223.00$ (Recurring cost per LoRaWAN node)
*   **Net Unit Saving (60 mo)**: $R302 - R223.00 = R79.00$

**The Calculation:**
$N = \frac{R6,735}{R79.00} = \mathbf{85.25}$

**Conclusion**: For 5 gateways over 5 years, the break-even point is exactly **85 sensors**.
*   **Below 85 sensors**: Mesh is cheaper due to avoiding R6,735 in gateway costs.
*   **Above 85 sensors**: LoRaWAN is cheaper as the R302 unit saving eventually offsets the infrastructure and LNS costs.

---

## 5. Conclusion

The updated LNS fee of **R3.7167 per device/month** further solidifies LoRaWAN's position as the most cost-effective solution for scaled deployments.

1.  **For Standard/Volume Deployments (>50 sensors)**: **LoRaWAN is the definitive winner.**
    *   The significant CAPEX savings on radio modules (**R120 vs R422**) create a massive financial cushion.
    *   LoRaWAN remains cheaper for a minimum of **6 to 6.6 years** (74-79 months) depending on scale. This duration likely exceeds the operational battery life of the sensors themselves.
    *   *Recommendation*: For any commercial or agricultural project where sensor volume is the primary driver, LoRaWAN offers the lowest Total Cost of Ownership (TCO) over the device lifecycle.

2.  **For High-Complexity/Low-Density Deployments (<20 sensors)**: **Mesh is the winner.**
    *   In environments requiring many gateways for few devices (e.g., mine shafts, extremely hilly terrain), Mesh's lower gateway cost (**R950 vs R2297**) and zero monthly fees make it the superior choice.
    *   Mesh starts cheaper and stays cheaper because the infrastructure savings are never eroded by recurring fees.

### Final Recommendation
**Standardize on LoRaWAN** for general-purpose IoT sensor networks. The "break-even" point has moved out to over 6 years, making the initial investment in higher-cost gateways more than justified by the long-term module savings. Use Mesh only as a tactical solution for extreme coverage gaps that cannot be economically reached via LoRaWAN.
