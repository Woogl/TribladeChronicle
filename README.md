# Triblade Chronicle
<img src="https://github.com/user-attachments/assets/4b70419e-9f91-4cfb-8267-a2415ccecdd2" height="400" />

*(Temporary BI)*

I am developing an action RPG game using Unreal Engine 5.4

# Dev History
### 1. Multiplayer Ability Input Binding
![Multiplayer Ability Input Binding](https://github.com/user-attachments/assets/0b55afa4-9dd7-48f3-9d16-9250940da970)

- Lyra-like pawn data (`AbilitySet`, `InputConfig`)
- Lyra-like components (`AbilitySystemComponent`, `InputComponent`)

### 2. Replicated Armed Locomotion
![Replicated Armed Locomotion](https://github.com/user-attachments/assets/1e51deeb-2ed1-4887-92b7-cea6be15bed5)

- `ABP_Hero` has unarmed/armed locomotion.
- `bWeaponEquipped` is replicated in `BP_Hero`.

>💾 2024.09.10

### 3. Health Attribute Set
![image](https://github.com/user-attachments/assets/fb4bb711-baed-4b15-991f-0cb689968c3b)

- Character has `HealthComponent`.
- `HealthComponent` handles events on health attribute change.

### 4. Death Ability
![TribladeChroniclePreviewNetMode_Standalone064-bit_PCD3DSM62024-09-1100-16-53-ezgif com-optimize](https://github.com/user-attachments/assets/6e8cc38d-664e-4026-9953-c3426cd0956f)

- GE_Damage_Instant

>💾 2024.09.11

### 5. Attack & Hit React Ability
![TribladeChroniclePreviewNetMode_Client164-bit_PCD3DSM62024-09-1400-29-00-ezgif com-optimize](https://github.com/user-attachments/assets/e2c3e7f6-ac96-435b-9b87-86d7f60bb67d)

- Take damage and turn to the instigator when attacked.
- This ability needs `NetExecutionPolicy::ServerInitiated`

>💾 2024.09.14

### 6. Targeting System
![TargetingSystem-ezgif com-optimize](https://github.com/user-attachments/assets/e54767b0-f323-4268-aca8-947eb4dfc509)

- I implemented it by combining two plugins.
  - **Gameplay targeting system**
    - https://dev.epicgames.com/documentation/unreal-engine/gameplay-targeting-system-in-unreal-engine
  - **Target system plugin**
    - https://github.com/mklabs/ue4-targetsystemplugin
   
>💾 2024.09.16

### 7. Combo Attack
![ComboAttack-ezgif com-optimize](https://github.com/user-attachments/assets/3a2f64ae-1172-40d4-b158-7a40fb5e4170)

- `ANS_ComboWindow`(Anim notify state) defines the duration of the next combo attack.

>💾 2024.09.22

### 8. Enemy Behaviour Tree
<img src="https://github.com/user-attachments/assets/cc253ce0-745f-4b6f-99dd-992f261f633e" height="300" />

- Enemy chase & attack

>💾 2024.09.29

### 9. Stun Ability
![TribladeChroniclePreviewNetMode_Client164-bit_PCD3DSM62024-10-0118-40-42-ezgif com-optimize](https://github.com/user-attachments/assets/b0f0d9ec-39f9-4d6c-962c-e7a854aaa2c1)

>💾 2024.10.01

### 10. Prevent Friendly Fire
![image](https://github.com/user-attachments/assets/23e624f6-48b8-4d34-bd32-ba71cb258f4b)

- Data-driven setting with Gameplay Targeting System. 

>💾 2024.10.03

### 11. MVVM Based View Binding
![image](https://github.com/user-attachments/assets/0966d2a6-ef62-4d07-aa6d-4455aac7593d)
![image](https://github.com/user-attachments/assets/9696335a-371c-479b-bb2c-4fb2b8e9d36d)

- **UMG Viewmodel documentation** 
    - https://dev.epicgames.com/documentation/en-us/unreal-engine/umg-viewmodel?application_version=5.4
 
>💾 2024.10.05

### 12. Repositioning During Attacks
![Repositioning](https://github.com/user-attachments/assets/b2b739e6-5330-46d9-b589-66fb5e231566)

- **UTcAbilityTask_LookAtTarget**
  - The source actor adjusts its yaw to face the target actor.

>💾 2024.10.06

### 13. Party System
- **Party System Initialization Process**
![partycomponent](https://github.com/user-attachments/assets/2cad511f-8eb6-48ea-8def-7ba598c71557)

>💾 2024.10.27

### 14. Party System With Mulityplayer
![ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/7ea3603b-268f-4db5-883d-09bb06a64213)

> 💾 2024.11.09
