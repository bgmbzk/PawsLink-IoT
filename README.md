# 🐾 PawsLink IoT: The Elite Cat Gate Controller

Selam! Bu proje, evin asıl sahibi olan kedimin balkon kapısında mahsur kalma krizlerine (ve benim her seferinde bir "kapı görevlisi" edasıyla yerimden kalkmama) son vermek için geliştirildi. Başta küçük bir can sıkıntısı gibi görünse de, süreç içinde evrim geçirerek tam kapsamlı bir **Embedded System & IoT** projesine dönüştü.

## 📸 Proje Görselleri
Aşağıda tasarımın şematik, PCB ve 3D modelleme aşamalarını görebilirsiniz:

| Schematic Design | PCB Layout | 3D Render |
| :---: | :---: | :---: |
| ![Schematic](./PawsLink_IoT_sch_png.png) | ![PCB](./PawsLink_IoT_pcb_png.png) | ![3D Render](./PawsLink_IoT_3d_png.png) |

## 🐱 Neden PawsLink?
Kedim, balkona çıkmak istediğinde kapının önünde kendine has bir frekansta seslenerek beni göreve çağırıyor. **PawsLink**, bu işitsel sinyalleri (miyavlamaları) algılayıp mekanik bir kolu tetikleyen, böylece kedime kendi özgürlüğünü sunan akıllı bir sistemdir.

## 🛠 Teknik Gelişim & Mühendislik Detayları
Proje başlangıçta **ATmega** tabanlıydı; ancak hem performansını artırmak hem de modern bağlantı özelliklerinden (Wi-Fi/Bluetooth) faydalanmak amacıyla mimariyi **ESP32**’ye taşıdım. Tasarımda dikkat ettiğim bazı kritik teknik noktalar:

* **RF Performansı (Anten Keep-out):** ESP32'nin üzerindeki PCB antenin verimli çalışması için, antenin altında kalan tüm katmanlarda bakır dökümü iptal edildi (No-copper zone).
* **Hassas PCB Layout:** USB-C güç girişi gibi yüksek yoğunluklu pinlerde kısa devre riskini önlemek için özel clearance (güvenlik mesafesi) ayarları yapıldı.
* **EMI ve Gürültü Yönetimi:** Güç hatları üzerine yerleştirilen decoupling kapasitörleri ile dijital gürültü minimize edildi, analog ses sensörünün daha kararlı çalışması sağlandı.
* **Hatasız Tasarım:** Endüstriyel standartlarda, **0 DRC Error** ve **0 Unconnected Items** ile üretime hazır hale getirildi.

## 📂 Dosya Yapısı
* `/Hardware`: KiCad şematik ve PCB layout dosyaları.
* `/Production`: Üretime hazır Gerber ve Drill dosyaları (PawsLink_Final_v1.zip).
* `/Firmware`: ESP32 için yazılmış IoT kontrol kodları.

---

### 🚀 Nasıl Çalışır?
1. PCB sipariş edilir ve bileşenler lehimlenir.
2. ESP32 yazılımı yüklenir.
3. Kedinin "meyak" frekansı kalibre edilir.
4. Koltuğa yaslanılır ve kedinin kendi kapısını açışı izlenir. ✨

---

**Not:** Bu proje yapılırken hiçbir kedi mahsur bırakılmamıştır. Aksine, artık evin kapıları onun kontrolü altında! 🐈‍⬛🚀
