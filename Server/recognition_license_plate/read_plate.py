import pytesseract
import cv2
from lib_detection import load_model, detect_lp, im2single
import pyautogui

while true:
    print("ok")

myScreenshot = pyautogui.screenshot()
myScreenshot.save(r'G:\\Study\\University\\Nam 4\\CNPMN\\Project\\SmartParking\\Server\\recognition_license_plate\\mycar.jpg')


pytesseract.pytesseract.tesseract_cmd = 'C:\\Program Files\\Tesseract-OCR\\tesseract.exe'

# Dinh nghia cac ky tu tren bien so
char_list =  '0123456789ABCDEFGHKLMNPRSTUVXYZ'

# Ham fine tune bien so, loai bo cac ki tu khong hop ly
def fine_tune(lp):
    newString = ""
    for i in range(len(lp)):
        if lp[i] in char_list:
            newString += lp[i]
    return newString


# Đường dẫn ảnh, các bạn đổi tên file tại đây để thử nhé
img_path = "G:\\Study\\University\\Nam 4\\CNPMN\\Project\\SmartParking\\Server\\recognition_license_plate\\mycar.jpg"

# Load model LP detection
wpod_net_path = "G:\\Study\\University\\Nam 4\\CNPMN\\Project\\SmartParking\\Server\\recognition_license_plate\\wpod-net_update1.json"
wpod_net = load_model(wpod_net_path)

# Đọc file ảnh đầu vào
Ivehicle = cv2.imread(img_path)





# Kích thước lớn nhất và nhỏ nhất của 1 chiều ảnh
Dmax = 608
Dmin = 288

# Lấy tỷ lệ giữa W và H của ảnh và tìm ra chiều nhỏ nhất
ratio = float(max(Ivehicle.shape[:2])) / min(Ivehicle.shape[:2])
side = int(ratio * Dmin)
bound_dim = min(side, Dmax)

_ , LpImg, lp_type = detect_lp(wpod_net, im2single(Ivehicle), bound_dim, lp_threshold=0.5)


if (len(LpImg)):

    # Chuyen doi anh bien so
    LpImg[0] = cv2.convertScaleAbs(LpImg[0], alpha=(255.0))

    # Chuyen anh bien so ve gray
    gray = cv2.cvtColor( LpImg[0], cv2.COLOR_BGR2GRAY)

    # cv2.imshow("Anh bien so sau chuyen xam", gray)

    # Ap dung threshold de phan tach so va nen
    binary = cv2.threshold(gray, 127, 255,
                         cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]

    # cv2.imshow("Anh bien so sau threshold", binary)


    # Nhan dien bien so. Cau hinh --psm 7 la de nhan dien 1 line only
    text = pytesseract.image_to_string(binary, lang="eng", config="--psm 7")
    print(fine_tune(text))
    

    # Viet bien so len anh
    # cv2.putText(Ivehicle,fine_tune(text),(50, 50), cv2.FONT_HERSHEY_PLAIN, 3.0, (0, 0, 255), lineType=cv2.LINE_AA)

    # Hien thi anh va luu anh ra file output.png
    # cv2.imshow("Anh input", Ivehicle)
    # cv2.imwrite("output.png",Ivehicle)
    cv2.waitKey()

    f = open("G:\\Study\\University\\Nam 4\\CNPMN\\Project\\SmartParking\\Server\\result.txt", "w")
    f.write(fine_tune(text))
    f.close()



cv2.destroyAllWindows()