# Konfiguracja Home Row Mods – Keychron Q10 Pro

## Aktualna konfiguracja (`config.h`)

```c
#define TAPPING_TERM 200
// #define PERMISSIVE_HOLD
#define QUICK_TAP_TERM 0
// #define HOLD_ON_OTHER_KEY_PRESS
#define DEBOUNCE 30
```

---

## Opis ustawień

### `TAPPING_TERM 200`
Czas w milisekundach, przez jaki klawisz musi być wciśnięty, aby uznać go za „hold" (modyfikator) zamiast „tap" (litera).
- Zalecany zakres: **150–220 ms**
- Domyślna wartość QMK to 200 ms i jest to optymalny punkt startowy
- Zbyt niska → przypadkowe aktywacje modyfikatorów przy normalnym pisaniu
- Zbyt wysoka → modyfikatory reagują wolno, trudno używać skrótów klawiszowych

### `QUICK_TAP_TERM 0`
Określa okno czasowe, w którym szybkie podwójne tapnięcie tego samego klawisza aktywuje auto-repeat zamiast rozpoznać drugie tapnięcie jako osobne.
- Wartość **0 = wyłącza auto-repeat** przy home row modach
- **To jest kluczowe ustawienie zapobiegające duplikatom** przy szybkim pisaniu
- Wartość > 0 (np. 80 ms) powoduje duplikaty, gdy naciśniesz home row mod i zaraz potem tę samą literę

### `PERMISSIVE_HOLD` – wyłączone
Gdy aktywne: aktywuje „hold" (modyfikator), gdy inny klawisz został wciśnięty i zwolniony, zanim upłynął `TAPPING_TERM`.
- **Nie zalecane przy `TAPPING_TERM` ≤ 200 ms** – powoduje zbyt wiele przypadkowych aktywacji modyfikatorów przy szybkim pisaniu
- Przydatne tylko przy bardzo wysokim `TAPPING_TERM` (np. 300+ ms)

### `HOLD_ON_OTHER_KEY_PRESS` – wyłączone
Gdy aktywne: aktywuje „hold" (modyfikator), gdy podczas trzymania home row moda zostanie naciśnięty jakikolwiek inny klawisz.
- **Silnie odradzane przy home row mods** – normalne szybkie pisanie (rolowanie klawiszy) ciągle aktywuje modyfikatory
- Główna przyczyna duplikatów i niechcianych skrótów klawiszowych przy szybkim pisaniu

### `DEBOUNCE 30`
Czas w milisekundach, przez jaki sygnał z klawisza musi być stabilny, by uznać go za wciśnięty.
- Zapobiega sprzętowemu „chatterowi" (wielokrotne wciśnięcia z jednego fizycznego naciśnięcia)
- Domyślna wartość QMK to 5 ms, ale dla stabilności warto używać 20–30 ms
- Zbyt niska → możliwy chatter (sprzętowe duplikaty)
- Zbyt wysoka → opóźnienie w rejestracji wciśnięcia (zwykle nieodczuwalne)

---

## Przyczyny duplikatów – diagnostyka

| Objaw | Prawdopodobna przyczyna | Rozwiązanie |
|---|---|---|
| Duplikaty przy szybkim pisaniu | `QUICK_TAP_TERM > 0` | Ustaw `QUICK_TAP_TERM 0` |
| Niechciane modyfikatory przy rolowaniu | `HOLD_ON_OTHER_KEY_PRESS` aktywne | Wyłącz tę opcję |
| Przypadkowe modyfikatory przy normalnym pisaniu | `PERMISSIVE_HOLD` + niski `TAPPING_TERM` | Wyłącz `PERMISSIVE_HOLD` |
| Podwójne znaki z jednego wciśnięcia | Sprzętowy chatter | Zwiększ `DEBOUNCE` do 35–40 |
| Modyfikatory zamiast liter | `TAPPING_TERM` zbyt niski | Zwiększ do 220–250 ms |

---

## Źródła

- [A Guide to Home Row Mods – precondition.github.io](https://precondition.github.io/home-row-mods)
- [QMK Tap-Hold Configuration](https://docs.qmk.fm/#/tap_hold)
