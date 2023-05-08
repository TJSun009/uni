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
        self.panel1 = wx.Panel(self)

        
        
        #Box Sizers

        #Main Box Sizer

        self.verticalBoxMain = wx.BoxSizer(wx.VERTICAL)

        #Selection Boxes
        self.btnBox1 = wx.BoxSizer(wx.HORIZONTAL)
        self.encryptionChoiceBtn = wx.Button(self.panel1, -1, "Encryption")
        self.btnBox1.Add(self.encryptionChoiceBtn, flag = wx.RIGHT, border = 10)
        self.Bind(wx.EVT_BUTTON, self.encryption, id = self.encryptionChoiceBtn.GetId())
        
        self.decryptionChoiceBtn = wx.Button(self.panel1, 0, "Decryption")
        self.btnBox1.Add(self.decryptionChoiceBtn, flag = wx.RIGHT, border = 10)
        self.Bind(wx.EVT_BUTTON, self.decryption, id = self.decryptionChoiceBtn.GetId())

        self.verticalBoxMain.Add(self.btnBox1, flag = wx.TOP|wx.BOTTOM|wx.LEFT, border = 10)        

        self.labelBox1 = wx.BoxSizer(wx.VERTICAL)
        
        self.msgEntryLabel = wx.StaticText(self.panel1, label = 'placeholder')
        self.labelBox1.Add(self.msgEntryLabel, flag = wx.TOP|wx.BOTTOM, border = 10)
        self.msgEntryLabel.Hide()

        self.verticalBoxMain.Add(self.msgEntryLabel, flag = wx.TOP|wx.BOTTOM|wx.LEFT, border = 10)
        
        #Text Box
        self.textBox = wx.BoxSizer(wx.HORIZONTAL)
        self.plaintxtInput = wx.TextCtrl(self.panel1, size = (300,20))
        self.plaintxtInput.Hide()
        self.textBox.Add(self.plaintxtInput, flag = wx.LEFT, border = 10)
        self.verticalBoxMain.Add(self.textBox, flag = wx.BOTTOM, border = 10)

        self.labelBox2 = wx.BoxSizer(wx.VERTICAL)
        self.verticalBoxMain.Add(self.labelBox2, flag = wx.BOTTOM, border = 10)
        
        self.btnBox2 = wx.BoxSizer(wx.HORIZONTAL)
        self.encryptBtn = wx.Button(self.panel1, 1, "Encrypt")
        self.btnBox2.Add(self.encryptBtn, flag = wx.RIGHT|wx.LEFT, border = 10, proportion = 0.2)
        self.encryptBtn.Hide()
        
        self.decryptBtn = wx.Button(self.panel1, 2, "Decrypt")
        self.btnBox2.Add(self.decryptBtn, flag = wx.RIGHT|wx.LEFT, border = 10, proportion = 0.2)
        self.decryptBtn.Hide()

        self.verticalBoxMain.Add(self.btnBox2, flag = wx.BOTTOM, border = 10)

        self.output = wx.StaticText(self.panel1, label = '')
        self.verticalBoxMain.Add(self.output, flag = wx.TOP|wx.BOTTOM|wx.LEFT, border = 10)

        self.Bind(wx.EVT_BUTTON, self.encrypt, id = self.encryptBtn.GetId())

        self.Bind(wx.EVT_BUTTON, self.decrypt, id = self.decryptBtn.GetId())
        
    
        self.panel1.SetSizer(self.verticalBoxMain)
        
        self.Show(True)

    def onQuit(self, e):
        self.Close()


    def encryption(self , e):
        #Could use CheckBox rather than Buttons
        self.msgEntryLabel.SetLabel('Enter Your Message:' )

        
        self.encryptionChoiceBtn.Hide()
        self.decryptionChoiceBtn.Hide()
      
        self.msgEntryLabel.Show()

        self.plaintxtInput.Show()
        self.encryptBtn.Show()

    def decryption(self , e):
        self.msgEntryLabel.SetLabel('Enter Your Encrypted Message:' )


        self.msgEntryLabel.Show()

        self.plaintxtInput.Show()

        self.decryptBtn.Show()

        self.padEntryLabel = wx.StaticText(self.panel1, label = 'Enter the Pad Code:')
        self.labelBox2.Add(self.padEntryLabel, flag = wx.LEFT|wx.BOTTOM|wx.TOP, border = 10)
        
        self.padCode = wx.TextCtrl(self.panel1, size = (300,20))
        self.labelBox2.Add(self.padCode, flag = wx.LEFT|wx.TOP, border = 10)
        
        self.encryptionChoiceBtn.Hide()
        self.decryptionChoiceBtn.Hide()

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
