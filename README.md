# Programos aprašymas

Tai programa, kuri nuskaito pasirinktą failą iš repozitorijos, suskaičiuoja, kiek kartų jame pasikartoja kiekvienas žodis, surašo eilutes, kuriose tie žodžiai yra, ir išrenka visas nuorodas iš teksto bei surašo jas į atskirą failą

# Kompiliavimo ir naudojimosi instrukcijos

1. Parsisiųsti Visual Studio kompiliatorių ir CMake
2. Nusiklonuoti repozitoriją savo kompiuteryje naudojant git clone arba parsisiųsti suzippintus failus iš Github
3. Atsidaryti komandinę eilutę (Windows Powershell arba Command Prompt) ir per ją nunaviguoti į programos direktoriją
4. Sukompiliuoti naudojant komandą "cmake -B build -S .; cmake --build build"
5. Paleisti naudojant komandą "./build/Debug/main.exe"

Prieš paleidžiant programą, į repozitoriją taip pat reikia įsikelti failą, kurį norite nuskaityti. Pasirinkus nuskaitomą failą, programa rezultatus surašo į tris failus - žodžius ir jų pasikartojimų kiekius į "zodziai.txt", eilutes, kuriose yra visi žodžiai į "cross-reference.txt", o nuorodas į "url.txt"