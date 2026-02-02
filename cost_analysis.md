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
| **Solar Panel (CAPEX)** | **R2,000.00** |  | Solar panels (100W) are needed for remote LoRaWAN gateways. |
| **Battery (CAPEX)** | **R8,000.00** | **R50.00** | Battery is needed for remote LoRaWAN gateways. |
| **Charger Controller (CAPEX)** | **R1,000.00** |  | Charger controller is needed for remote LoRaWAN gateways. |
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
*   **LoRaWAN OPEX**: 1000 * R3.7168 = **R3,716.80 / month**
*   **Break Even Time**: R295,265.00 / R3,716.80 ≈ **79 months**
*Result: LoRaWAN is cheaper for the first **6.6 Years**. After 6.7 years, the cumulative monthly fees exceed the one-time savings on modules.

### Scenario B: Medium Scale (100 Sensors, 2 Gateway one solar powered)
*Context: A typical smart-farm.*
*   **LoRaWAN CAPEX**: (R2,297.00 * 2 + (R2,000.00 + R8,000.00 + R1,000.00)) + (100 * R120.00) = R15,594.00 + R12,000.00 = **R 27,594.00**
*   **Mesh CAPEX**: (R950.00 * 2) + (100 * R422.00) = R1,900.00 + R42,200.00 = **R 44,100.00**
*   **Initial Diff**: LoRaWAN is **R16,506.00 cheaper**.
*   **LoRaWAN OPEX**: R3.7168 * 100 = **R 371.68 / month**
*   **Break Even Time**: R16,506.00 / R 371.68 ≈ **44 months**
*Result: Consistent with the large scale; LoRaWAN wins for any project shorter than **~3.6 years**.

### Scenario C: Small & Complex (10 Sensors, 5 Gateways four solar powered)
*Context: A confusing layout (tunnels/basements/hills) requiring many gateways for few devices.*
*   **LoRaWAN CAPEX**: (R2,297.00 * 5 + (R2,000.00 + R8,000.00 + R1,000.00) * 4) + (R 120.0 * 10) = R 11,485.00 + R 44,000.00 + R 1,200.00 = **R 56,685.00**
*   **Mesh CAPEX**: (R 950.00 * 5) + (R 422.00 * 10) = R 4,750.00 + R 4,220.00 = **R 8,970.00**
*   **Initial Diff**: Mesh is **R47,715.00 cheaper** upfront.
*   **LoRaWAN OPEX**: R3.7168 * 10 = **R 37.17 / month**
*Result: Mesh starts cheaper and **stays cheaper forever**. LoRaWAN never catches up because it has significantly higher CAPEX *and* higher OPEX in this scenario.

### 4.4 Exact Break-Even Point (5 Gateways four solar powered, 60 Months)
To find the exact number of nodes N where LoRaWAN and Mesh costs are equal over a 5-year (60 month) period with 5 Gateways:

**The Variables:**
*   **LoRaWAN Infrastructure**: (R 2,297.00 * 5) + (R 11,000.00 * 4) = R 55,485.00
*   **Mesh Infrastructure**: (R 950.00 * 5) = R 4,750.00
*   **Gateway Cost Diff**: R 55,485.00 - R 4,750.00 = R 50,735.00 (Infrastructure debt of LoRaWAN)
*   **Module Cost Diff (CAPEX)**: R 422.00 - R 120.00 = R 302.00 (Once-off upfront saving per LoRaWAN node)
*   **Operational Cost (OPEX - 60 mo)**: R 3.7168 * 60 ≈ R 223.01 (Total recurring LNS cost over 5 years)
*   **Net Unit Saving (60 mo)**: R 302.00 - R 223.01 = R 78.99

**The Calculation:**
N = R 50,735.00 / R 78.99 ≈ 642.3

**Conclusion**: For 5 gateways over 5 years, the break-even point is approximately **642 sensors**.
*   **Below 642 sensors**: Mesh is cheaper due to avoiding R 50,735 in gateway and LNS infrastructure costs.
*   **Above 642 sensors**: LoRaWAN is cheaper as the module cost savings eventually offset the infrastructure and LNS fees.

---

The inclusion of the **R 3.7167 LNS fee** and high-capacity **Solar Infrastructure (R 11,000 per remote site)** shifts the financial viability significantly based on deployment topology and density.

1.  **High-Density / Grid-Powered (Scenario A/B)**: **LoRaWAN is the winner.**
    *   If grid power is available (eliminating solar costs) OR if density exceeds **650 sensors** per 5 gateways, the R 120 module cost provides an unbeatable TCO.
    *   *Recommendation*: Use LoRaWAN for large commercial hubs or sites with pre-existing power infrastructure.

2.  **Distributed / Solar-Powered (Scenario B/4.4)**: **Mesh is the winner.**
    *   When solar/battery kits (R 11,000 each) are required for gateways, the "Infrastructure Debt" scales to **R 13,297 per site**.
    *   In a typical farm layout (e.g., 100 sensors across 5 solar gateways), the R 302 module saving is not enough to offset the R 50,000+ infrastructure premium and recurring LNS fees.
    *   *Recommendation*: Use Mesh for typical agricultural deployments where sensor density per gateway is low to moderate.

3.  **Small & Complex (Scenario C)**: **Mesh is the definitive winner.**
    *   In environments requiring many gateways for very few devices (e.g., mine shafts, extremely hilly terrain, small remote outposts), Mesh's R 950 gateway cost and zero monthly fees make it the only logical choice.
    *   LoRaWAN in this scenario starts R 47,000 more expensive and the gap widens every month due to LNS fees.
    *   *Recommendation*: Use Mesh as a tactical solution for coverage gaps and low-density remote monitoring.

### Final Recommendation
**Standardize on Mesh for small-to-medium agricultural deployments (under 600 nodes)** where solar-powered gateways are required for coverage. The "Infrastructure Debt" created by solar-powered LoRaWAN gateways (R13,297/site) and the LNS fees only make sense at extreme scale.

**Use LoRaWAN only as a tactical solution** for high-density industrial clusters or locations with existing grid-powered gateways where the CAPEX savings on the R120 modules can be realized without the solar infrastructure overhead.
