# Triblade Chronicle
<img src="https://github.com/user-attachments/assets/4b70419e-9f91-4cfb-8267-a2415ccecdd2" height="400" />

*(Temporary BI)*

I am developing an action RPG game using Unreal Engine 5.4

# Dev History
### 1. Multiplayer Ability Input Binding
![Multiplayer Ability Input Binding](https://github.com/user-attachments/assets/0b55afa4-9dd7-48f3-9d16-9250940da970)

- Lyra-like pawn data (`AbilitySet`, `InputConfig`)
- Lyra-like pawn components (`AbilitySystemComponent`, `InputComponent`)

### 2. Replicated Armed Locomotion
![Replicated Armed Locomotion](https://github.com/user-attachments/assets/1e51deeb-2ed1-4887-92b7-cea6be15bed5)

- ABP has unarmed/armed locomotion.
- `bWeaponEquipped` value is replicated in BP_Character.

>💾 2024.09.10

### 3. Health Attribute Set
![image](https://github.com/user-attachments/assets/fb4bb711-baed-4b15-991f-0cb689968c3b)

- Character has `HealthComponent`.
- `HealthComponent` handles events on health attribute change.

### 4. Death Ability
![TribladeChroniclePreviewNetMode_Standalone064-bit_PCD3DSM62024-09-1100-16-53-ezgif com-optimize](https://github.com/user-attachments/assets/6e8cc38d-664e-4026-9953-c3426cd0956f)

- GE_Damage_Instant

>💾 2024.09.11

### 5. Hit React Abiliy
![TribladeChroniclePreviewNetMode_Client164-bit_PCD3DSM62024-09-1400-29-00-ezgif com-optimize](https://github.com/user-attachments/assets/e2c3e7f6-ac96-435b-9b87-86d7f60bb67d)

- Take damage and turn to the instigator when attacked.
- This ability needs `NetExecutionPolicy::ServerInitiated`

>💾 2024.09.14
