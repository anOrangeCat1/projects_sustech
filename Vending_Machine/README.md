# Implementing an Automatic Vending Machine Using Logic Circuits

In this project, I was responsible for logic circuit design and simulating it in Multisim.

Firstly, I designed every part of whole circuit to complete specific functions, such as inserting 1 yuan, inserting 5 yuan or accelaration of all money and so on. 

Only some basic chips were used, such as adders and decoders.

Each part circuit was named by its function, and whole logic circuit, which could work as a vending machine, was named **"Vending_Machine_System.ms14"**.

Also, the pre ppt and report were attached.

**_Below are the relevant files:_**
|folder_name/file_name|content&function|
|------|------|
|_Circuit_network_testing.ms14_|**Circuit networks designed to avoid complex wiring issues.**|
|_Cumulative_coin_insertion_total.ms14_|**Accumulated coin counting circuit implementation, which can calculate the total amount of coins inserted and display it.**|
|_Design_Ideas_for_Vending_Machines.txt_|**Design ideas document.**|
|_Inserting_1_yuan_coin.ms14_|**Circuit implementation for the 5 yuan coin insertion part.**|
|_Inserting_5_yuan_coin.ms14_|**Circuit implementation for the 1 yuan coin insertion part.**|
|_State_machine_prototype.ms14_|**Circuit implementation of the state machine section that can achieve state transitions for selecting items, technical operations, and coin insertion.**|
|_Vending machine_4bit.ms14_|**The 4-bit version of the project integrates all functions.**|
|_Vending_machine.ms14_|**The final version of the project integrates all functions.**|
|_Vending_machine_system.docx_|**The project's final presentation slides.**|
|_Vending_machine_system.pptx_|**The project's final report.**|

Final logic circuit was like below:
<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/8a5ef7bf-3041-471a-b78f-958ff6d2519f"  />
</div>

-----------------------------------------------------------------------------------------------------
**The technical description of the design ideas for the vending machine, which was in _Design_Ideas_for_Vending_Machines.txt_** 
1. Standby: Wait for confirmation and exit standby mode to enter State 2.
2. Coin Insertion: After coin insertion, confirm and enter State 3.
3. Product Selection: After selecting the desired product, confirm and enter State 4.
4. Result Determination:
	If there is enough money, dispense the product and give change.
	If there is not enough money, refund the full amount.
	After confirmation, return to State 1 (standby mode) to complete one work cycle.
There are a total of 4 states, all of which require confirmation to enter the next state. You can use a state loop with a circular counter and an additional CLR interface to reset it after each cycle.

**Coin Insertion Module:**

1 Yuan Coin Insertion Module: Implemented using a 74LS161N adder.
	Maximum cumulative amount: 15 yuan (4 digits).
5 Yuan Coin Insertion Module: Implemented using a 74LS161N adder and a 74LS138D decoder.
	Maximum cumulative amount: 15 yuan (4 digits).
Accumulate 1 yuan and 5 yuan coins together, expanding the adder to 30 (5 digits).
	Maximum amount: 30 yuan, meaning the maximum purchase amount for a drink is 30 yuan.
 

**Product Selection Module:**

Product Selector: 4 types of products (e.g., 2 yuan for Nongfu Spring, 3 yuan for Cola, 4 yuan for Nongfu Orchard, 5 yuan for Xiaoming).
Similar to the coin insertion module, it uses a 74LS161N adder and a 74LS138D decoder to select products.


**Change Module:**

Design a full subtractor using 4008BD and 4070BD.
Implementing 5-bit binary subtraction (4008BD can only implement 4-bit full subtraction).
Logic:There are four possible scenarios for the first bit (most significant bit):

1. Coin Total: 0xxxx, Product Amount Total: 0xxxx
2. Coin Total: 0xxxx, Product Amount Total: 1xxxx (directly refund full amount)
3. Coin Total: 1xxxx, Product Amount Total: 0xxxx
4. Coin Total: 1xxxx, Product Amount Total: 1xxxx

In the first case, simply subtract the last four bits. If there's a borrow, refund the full amount; otherwise, output the result.
In the second case, directly refund the full amount.
In the third case, subtract the last four bits first, then add binary 16. This involves using two's complement calculations.
In the fourth case, subtract the last four bits. If there's a borrow, refund the full amount; otherwise, output the result.

Use a decoder to distinguish the four cases based on the most significant bit.
Note that the first and fourth cases are the same, and they can share the same connector.
Alternatively, you can design a 5-bit or higher-bit full subtractor to simplify the process.


