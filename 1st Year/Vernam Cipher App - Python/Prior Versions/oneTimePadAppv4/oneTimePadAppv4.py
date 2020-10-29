import wx
from ciphersv2 import*
from datetime import datetime
import io

#resizing sorted in this version
#You can return multiple things in python


class oneTimePadApp(wx.Frame):
    def __init__(self, *args, **kwargs):
        super(oneTimePadApp, self).__init__(*args, **kwargs)

        self.initUI()
        
    def initUI(self):
        self.SetSize(350,350)
        self.SetTitle("Vernam Cipher App")

        icon = wx.Icon('Vc_Icon.ico', wx.BITMAP_TYPE_ICO)

        self.SetIcon(icon)
        
        self.panel1 = wx.Panel(self)

        #Menu Bar

        self.menuBar = wx.MenuBar()

        self.modeMenu = wx.Menu()

        self.encryptionChoice = wx.MenuItem(self.modeMenu, 1, text = "Encrypt", kind = wx.ITEM_NORMAL)
        self.modeMenu.Append(self.encryptionChoice)

        self.modeMenu.AppendSeparator()
        
        self.decryptionChoice = wx.MenuItem(self.modeMenu, 2, text = "Decrypt", kind = wx.ITEM_NORMAL)
        self.modeMenu.Append(self.decryptionChoice)

        self.menuBar.Append(self.modeMenu, '&Mode')
        
        self.docsMenu = wx.Menu()

        self.viewPrior = wx.MenuItem(self.docsMenu, 3, text = "View Prior Data", kind = wx.ITEM_NORMAL)
        self.docsMenu.Append(self.viewPrior)
        
        self.menuBar.Append(self.docsMenu, '&Docs')

        self.SetMenuBar(self.menuBar)

        self.Bind(wx.EVT_MENU, self.menuhandler)
        
        
        #Box Sizers

        #Main Box Sizer

        self.verticalBoxMain = wx.BoxSizer(wx.VERTICAL)


        #Label and TextBox
        
        self.textBox = wx.BoxSizer(wx.VERTICAL)
        
        self.msgEntryLabel = wx.StaticText(self.panel1, wx.ID_ANY, label = 'placeholder')
        self.textBox.Add(self.msgEntryLabel, flag = wx.TOP|wx.BOTTOM, border = 5)
        
        self.plaintxtInput = wx.TextCtrl(self.panel1, wx.ID_ANY, size = (300,20))
        self.textBox.Add(self.plaintxtInput, flag = wx.TOP|wx.BOTTOM, border = 5)
        self.verticalBoxMain.Add(self.textBox, flag = wx.TOP|wx.BOTTOM|wx.LEFT, border = 10)

        self.textBox.ShowItems(show = False)

        #Ciphertext Menu

        self.labelBox2 = wx.BoxSizer(wx.VERTICAL)
        self.verticalBoxMain.Add(self.labelBox2)

        
        #Encrypt/Decrypt Button
        self.btnBox2 = wx.BoxSizer(wx.HORIZONTAL)
        self.encryptBtn = wx.Button(self.panel1, 4, "Encrypt")
        self.btnBox2.Add(self.encryptBtn, flag = wx.RIGHT|wx.LEFT, border = 10, proportion = 0.2)
        
        self.decryptBtn = wx.Button(self.panel1, 5, "Decrypt")
        self.btnBox2.Add(self.decryptBtn, flag = wx.RIGHT|wx.LEFT, border = 10, proportion = 0.2)
        
        self.btnBox2.ShowItems(show = False)

        self.verticalBoxMain.Add(self.btnBox2, flag = wx.BOTTOM, border = 10)

        self.output = wx.StaticText(self.panel1, label = '')
        self.verticalBoxMain.Add(self.output, flag = wx.TOP|wx.BOTTOM|wx.LEFT, border = 10)

        self.Bind(wx.EVT_BUTTON, self.encrypt, id = self.encryptBtn.GetId())

        self.Bind(wx.EVT_BUTTON, self.decrypt, id = self.decryptBtn.GetId())

        self.panel1.SetSizer(self.verticalBoxMain)
        self.panel1.Layout()
        
        self.Show(True)

    def onQuit(self, e):
        self.Close()

    def menuhandler(self, e):
        id = e.GetId()
        if id == self.encryptionChoice.GetId():
            self.encryption(e)
        elif id == self.decryptionChoice.GetId():
            self.decryption(e)
        elif id == self.viewPrior.GetId():
            import subprocess
            subprocess.call(['notepad.exe', 'One Time Pad Data.txt'])
            '''os.startfile('One Time Pad Data.txt')
            with io.open("One Time Pad Data.txt", "r", encoding="utf-8") as records:
                print(records.read())
                records.close()'''

            
    def encryption(self , e):
        self.msgEntryLabel.SetLabel('Enter Your Message :' )
        self.textBox.ShowItems(show = True)
        self.btnBox2.ShowItems(show = True)
        self.labelBox2.ShowItems(show = False)
        self.decryptBtn.Hide()
        self.panel1.Layout()

    def decryption(self , e):
        self.msgEntryLabel.SetLabel('Enter Your Ciphertext :' )
        
        self.textBox.ShowItems(show = True)
        
        self.btnBox2.ShowItems(show = True)
        self.encryptBtn.Hide()

        self.padEntryLabel = wx.StaticText(self.panel1, label = 'Enter the Pad Code:')
        self.labelBox2.Add(self.padEntryLabel, flag = wx.LEFT|wx.BOTTOM|wx.TOP, border = 10)
        
        self.padCode = wx.TextCtrl(self.panel1, size = (300,20))
        self.labelBox2.Add(self.padCode, flag = wx.LEFT|wx.TOP|wx.BOTTOM, border = 10)

        
        self.panel1.Layout()

    def encrypt(self, e):
        plaintext = self.plaintxtInput.GetValue()
        pad = ""
        ciphertext = ''

        message = one_time_pad(plaintext, ciphertext, pad).encrypt()

        ciphertext = message[0]
        pad = message[1]

        output = 'Ciphertext: |{}|  Pad Code: |{}|'.format(ciphertext,pad)
        
        self.output.SetLabel(output)

        with io.open("One Time Pad Data.txt", "a", encoding="utf-8") as records:
            now = datetime.now().strftime("%d/%m/%Y %H:%M:%S")
        
            records.write('\nStored on: {}\n at {}\n\n'.format(now,output))

            records.close()

        print(output)

    def decrypt(self, e):
        '''plaintxt becomes ciphertxt input'''
        ciphertext = self.plaintxtInput.GetValue()
        pad = self.padCode.GetValue()
        
        encrypted_message = one_time_pad("", ciphertext, pad)

        plaintext = encrypted_message.decrypt()
        
        self.output.SetLabel('Plaintext: {}'.format(plaintext))
        print (plaintext)
        

def main():
    app = wx.App()
    oneTimePadApp(None)
    app.MainLoop()

if __name__ == '__main__':
    main()
