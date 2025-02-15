bl_info = {
    "name": "Barebones FBX Exporter",
    "blender": (4, 0, 0),  # Set to the appropriate version you are using
    "category": "Import-Export",
    "author": "Pedro Casas Martinez",
    "description": "Barebones FBX Exporter",
    "version": (1, 0),
    "support": "COMMUNITY",
}

import bpy
import os

class BarebonesFBXExporter(bpy.types.Operator):
    """Barebones FBX Exporter"""
    bl_idname = "export.barebones_fbx"
    bl_label = "Barebones FBX Exporter"
    bl_options = {'REGISTER', 'UNDO'}
    
    def execute(self, context):
        export_settings = context.scene.barebones_fbx_settings
        self.export_fbx(export_settings)
        return {'FINISHED'}
    
    def export_fbx(self, export_settings):
        filepath = export_settings.filepath;
        if filepath.startswith("//"):
            filepath = bpy.path.abspath(filepath)
            
        os.makedirs(os.path.dirname(filepath), exist_ok=True)
        bpy.ops.export_scene.fbx(
            filepath=filepath,
            check_existing=False,
            use_selection=export_settings.export_selected,
            apply_unit_scale=True,
            use_space_transform=True,
            global_scale=0.01,
            axis_forward='-Z',
            axis_up='Y',
            bake_space_transform=True
        )
        self.report({'INFO'}, f"Exported FBX to: {filepath}")
        print(f"Exported FBX to: {filepath}")

class BarebonesFBXSettings(bpy.types.PropertyGroup):
    filepath: bpy.props.StringProperty(name="FBX File Path", subtype='FILE_PATH')
    export_selected: bpy.props.BoolProperty(name="Export Selected Objects", default=False)

# UI Panel
class BAREBONES_PT_FBXExporterPanel(bpy.types.Panel):
    """Creates a panel in the Scene properties"""
    bl_label = "Barebones FBX Exporter"
    bl_idname = "BAREBONES_PT_fbx_exporter"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = "Barebones FBX Export"
    
    def draw(self, context):
        layout = self.layout
        export_settings = context.scene.barebones_fbx_settings
        
        layout.prop(export_settings, "filepath")
        layout.prop(export_settings, "export_selected")
        layout.separator()
        layout.operator("export.barebones_fbx", text="Export FBX")

# Register classes
def register():
    bpy.utils.register_class(BarebonesFBXExporter)
    bpy.utils.register_class(BarebonesFBXSettings)
    bpy.utils.register_class(BAREBONES_PT_FBXExporterPanel)
    bpy.types.Scene.barebones_fbx_settings = bpy.props.PointerProperty(type=BarebonesFBXSettings)

def unregister():
    bpy.utils.unregister_class(BarebonesFBXExporter)
    bpy.utils.unregister_class(BarebonesFBXSettings)
    bpy.utils.unregister_class(BAREBONES_PT_FBXExporterPanel)
    del bpy.types.Scene.barebones_fbx_settings

if __name__ == "__main__":
    register()