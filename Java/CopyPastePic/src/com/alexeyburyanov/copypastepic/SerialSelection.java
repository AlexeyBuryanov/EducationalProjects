package com.alexeyburyanov.copypastepic;

import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.io.Serializable;
import java.util.logging.Level;
import java.util.logging.Logger;

class SerialSelection implements Transferable {

    private Serializable obj = null;

    public SerialSelection(Serializable obj) {
        this.obj = obj;
    }

    public DataFlavor[] getTransferDataFlavors() {
        try {
            Class type = obj.getClass();
            String mimetype = "application/x-java-serialized-object;class=" + type.getName();
            return new DataFlavor[]{new DataFlavor(mimetype)};
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(SerialSelection.class.getName()).log(Level.SEVERE, null, ex);
            return new DataFlavor[0];
        }
    }

    public boolean isDataFlavorSupported(DataFlavor flavor) {
        return "application".equals(flavor.getPrimaryType())
                && "x-java-serialized-object".equals(flavor.getSubType())
                && flavor.getRepresentationClass().isAssignableFrom(obj.getClass());
    }

    public Object getTransferData(DataFlavor flavor) {
        if(!isDataFlavorSupported(flavor)) return null;
        return obj;
    }
}